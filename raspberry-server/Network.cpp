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

Network::Network()
{
    if(enet_initialize() != 0)
        exit(EXIT_FAILURE);
    pthread_create(&thread, NULL, &readThread, NULL);
}

void *Network::readThread(void *)
{
    int serviceResult = 1;
    ENetEvent event;
    ENetAddress address;
    address.host = ENET_HOST_ANY;
    address.port = 1400;
    server = enet_host_create(&address, 1, 1, 0, 0);
    if (server != NULL) {
        while(true) {
            serviceResult = 1;
            while(serviceResult > 0) {
                serviceResult = enet_host_service (server, &event, 1000);
                switch (event.type) {
                case ENET_EVENT_TYPE_CONNECT:
                    printf ("Client connected.\n");
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
                    printf ("Client disconected.\n");
                    client = NULL;
                    break;
                default:
                    break;
                }
            }
        }
    }
    return 0;
}

void Network::send(char opcode, const void * data, size_t dataLength, bool reliable)
{
    if(client) {
        char *ptr = new char[dataLength +1]();
        ptr[0] = opcode;
        memcpy(ptr + 1, data, dataLength);
        ENetPacket * packet = enet_packet_create (ptr, dataLength + 1, (reliable) ? ENET_PACKET_FLAG_RELIABLE : ENET_PACKET_FLAG_UNRELIABLE_FRAGMENT);
        enet_peer_send(client, 0, packet);
        enet_host_flush(server);
    }
}

Network::~Network()
{
    enet_host_destroy(server);
    enet_deinitialize();
}
