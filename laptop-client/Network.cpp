/* ====================================================================
 * This file is part of Raspcopter.
 *
 * Copyright (C) 2014 - Florent Revest <florent.revest666@gmail.com>

 * Raspcopter is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * Raspcopter is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with Raspcopter.  If not, see <http://www.gnu.org/licenses/>.
 * ================================================================== */

#include "Network.h"

ENetHost *Network::client = NULL;
ENetPeer *Network::server = NULL;

struct thread_args {
    char *ip;
    Network *instance;
} thread_args;

Network::Network(char *ip) : QObject()
{
    m_ip = ip;
    if(enet_initialize() != 0)
        exit(EXIT_FAILURE);
    struct thread_args *args = new struct thread_args;
    args->ip = ip;
    args->instance = this;
    pthread_create(&thread, NULL, &readThread, (void *)args);
}

void *Network::readThread(void *context)
{
    struct thread_args *args = (struct thread_args *)context;
    char *ip = args->ip;
    Network *instance = args->instance;
    int serviceResult = 1;
    ENetEvent event;
    ENetAddress address;

    client = enet_host_create(NULL, 1, 1, 0, 0);
    if (client == NULL)
        return (void*)1;

    enet_address_set_host (&address, ip);
    address.port = 1400;
    server = enet_host_connect (client, &address, 1, 0);
    if (server == NULL)
        return (void*)2;

    if (!(enet_host_service (client, &event, 5000) > 0 && event.type == ENET_EVENT_TYPE_CONNECT))
        return (void*)3;

    while(true) {
        serviceResult = 1;
        while(serviceResult > 0) {
            serviceResult = enet_host_service (client, &event, 1000);
            switch (event.type) {
            case ENET_EVENT_TYPE_CONNECT:
                server = event.peer;
                emit instance->connected();
                break;
            case ENET_EVENT_TYPE_RECEIVE:
                switch(event.packet->data[0]) {
                case SET_MEASURED_VALUES:
                    float values[3];
                    memcpy(values, event.packet->data + 1, sizeof(float) * 3);
                    emit instance->setMeasuredValues(values[0], values[1], values[2]);
                    break;
                case SET_CPU_USAGE:
                    emit instance->setCPUUsage(event.packet->data[1]);
                    break;
                case SET_MEMORY_USAGE:
                    emit instance->setMemoryUsage(event.packet->data[1]);
                    break;
                }
                enet_packet_destroy(event.packet);
                break;
            case ENET_EVENT_TYPE_DISCONNECT:
                server = NULL;
                emit instance->disconnect();
                break;
            default:
                break;
            }
        }
    }
    return (void*)0;
}

void Network::send(char opcode, const void *data, size_t dataLength, bool reliable)
{
    if(client) {
        char* ptr = new char[dataLength+1]();
        ptr[0] = opcode;
        memcpy(ptr+1, data, dataLength);

        ENetPacket * packet = enet_packet_create (ptr, dataLength + 1, (reliable) ? ENET_PACKET_FLAG_RELIABLE : ENET_PACKET_FLAG_UNRELIABLE_FRAGMENT);
        enet_peer_send(server, 0, packet);
        enet_host_flush(client);
    }
}

Network::~Network()
{
    ENetEvent event;
    enet_peer_disconnect(server, 0);
    while (enet_host_service (client, &event, 3000) > 0) {
        if(event.type == ENET_EVENT_TYPE_RECEIVE)
            enet_packet_destroy (event.packet);
        else if(event.type == ENET_EVENT_TYPE_DISCONNECT)
            break;
    }
    enet_host_destroy(client);
    enet_deinitialize();
}

char *Network::ip()
{
    return m_ip;
}
