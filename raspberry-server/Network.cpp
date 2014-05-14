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
#include "PID.h"

extern PID y_pid, p_pid, r_pid;
extern float y_target, p_target, r_target, throttle;

ENetPeer *Network::client = NULL;
ENetHost *Network::server = NULL;
pthread_mutex_t Network::net_mutex = PTHREAD_MUTEX_INITIALIZER;    

Network::Network()
{
    if(enet_initialize() != 0)
        abort();
    pthread_create(&thread, NULL, &readThread, NULL);
}

void *Network::readThread(void *)
{
    ENetEvent event;
    ENetAddress address;
    address.host = ENET_HOST_ANY;
    address.port = 1400;
    server = enet_host_create(&address, 1, 1, 0, 0);
    if(server == NULL)
        abort();

    while(true) {
        pthread_mutex_lock(&net_mutex);
        enet_host_service (server, &event, 0);
        pthread_mutex_unlock(&net_mutex);
        switch (event.type) {
        case ENET_EVENT_TYPE_CONNECT:
            client = event.peer;
            break;
        case ENET_EVENT_TYPE_RECEIVE:
            switch(event.packet->data[0]) {
            case SET_WANTED_ROLL:
                memcpy(&r_target, event.packet->data + 1, sizeof(float));
                break;
            case SET_WANTED_PITCH:
                memcpy(&p_target, event.packet->data + 1, sizeof(float));
                break;
            case SET_WANTED_YAW:
                memcpy(&y_target, event.packet->data + 1, sizeof(float));
                break;
            case SET_WANTED_THROTTLE:
                memcpy(&throttle, event.packet->data + 1, sizeof(float));
                break;
            case SET_PID_VALUES:
                float values[9];
                memcpy(values, event.packet->data + 1, sizeof(float) * 9);
                r_pid.setConstants(values[0], values[1], values[2]);
                p_pid.setConstants(values[3], values[4], values[5]);
                y_pid.setConstants(values[6], values[7], values[8]);
                break;
            }
            enet_packet_destroy(event.packet);
            break;
        case ENET_EVENT_TYPE_DISCONNECT:
            client = NULL;
            break;
        default:
            break;
        }
        usleep(100);
    }
    return 0;
}

void Network::send(char opcode, const void * data, size_t dataLength, bool reliable)
{
    char *ptr = new char[dataLength +1]();
    ptr[0] = opcode;
    memcpy(ptr + 1, data, dataLength);
    ENetPacket * packet = enet_packet_create (ptr, dataLength + 1, (reliable) ? ENET_PACKET_FLAG_RELIABLE : ENET_PACKET_FLAG_UNRELIABLE_FRAGMENT);
       
    pthread_mutex_lock(&net_mutex);
    if(client) {
        enet_peer_send(client, 0, packet);
        enet_host_flush(server);
    }
    pthread_mutex_unlock(&net_mutex);
}

Network::~Network()
{
    enet_host_destroy(server);
    enet_deinitialize();
}

