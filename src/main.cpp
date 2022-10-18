#include <stdio.h>
#include <bitset>
#include <iostream>
#include <math.h>
#include "core-fusion.h"
#include "profileapi.h"
// #include <chrono>

#define NUM_PARTICLES 128

#define MIN(a, b) ((a) < (b) ? (a) : (b))

class ParticleFilter : public CfPipe<uint32_t, uint16_t>
{
public:
    void run(CfStream<uint32_t> &istream, CfStream<uint16_t> &ostream)
    {
        //Map array
        uint8_t obstacle_x[800] = {0,1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16,17,18,19,20,21,22,23,24,25,26,27,28,29,30,31,32,33,34,35,36,37,38,39,40,41,42,43,44,45,46,47,48,49,50,51,52,53,54,55,56,57,58,59,60,61,62,63,64,65,66,67,68,69,70,71,72,73,74,75,76,77,78,79,80,81,82,83,84,85,86,87,88,89,90,91,92,93,94,95,96,97,98,99,100,101,102,103,104,105,106,107,108,109,110,111,112,113,114,115,116,117,118,119,120,121,122,123,124,125,126,127,128,129,130,131,132,133,134,135,136,137,138,139,140,141,142,143,144,145,146,147,148,149,0,149,0,149,0,149,0,149,0,149,0,149,0,149,0,149,0,149,0,149,0,149,0,149,0,149,0,149,0,149,0,149,0,149,0,149,0,149,0,149,0,149,0,149,0,149,0,149,0,149,0,82,83,84,85,86,87,88,89,90,91,149,0,82,91,149,0,82,91,149,0,82,91,149,0,82,91,149,0,82,91,149,0,82,91,149,0,82,91,149,0,82,91,149,0,82,91,149,0,82,83,84,85,86,87,88,89,90,91,149,0,149,0,149,0,149,0,149,0,41,42,43,44,45,46,47,48,49,50,149,0,41,50,149,0,41,50,149,0,41,50,149,0,41,50,149,0,41,50,149,0,41,50,149,0,41,50,149,0,41,50,149,0,41,42,43,44,45,46,47,48,49,50,149,0,149,0,149,0,149,0,149,0,149,0,149,0,149,0,149,0,149,0,149,0,149,0,149,0,149,0,149,0,149,0,149,0,149,0,149,0,149,0,149,0,149,0,149,0,149,0,149,0,149,0,149,0,149,0,149,0,149,0,149,0,149,0,34,35,36,37,38,39,40,41,42,43,149,0,34,43,149,0,34,43,149,0,34,43,149,0,34,43,96,97,98,99,100,101,102,103,104,105,149,0,34,43,96,105,149,0,34,43,96,105,149,0,34,43,96,105,149,0,34,43,96,105,149,0,34,35,36,37,38,39,40,41,42,43,96,105,149,0,96,105,149,0,96,105,149,0,96,105,149,0,96,97,98,99,100,101,102,103,104,105,149,0,149,0,83,84,85,86,87,88,89,90,91,92,149,0,83,92,149,0,83,92,149,0,83,92,149,0,83,92,149,0,83,92,149,0,83,92,149,0,83,92,149,0,83,92,149,0,83,84,85,86,87,88,89,90,91,92,149,0,149,0,149,0,149,0,149,0,149,0,149,0,149,0,149,0,149,0,149,0,149,0,149,0,149,0,149,0,149,0,149,0,149,0,149,0,149,0,149,0,149,0,149,0,149,0,149,0,149,0,149,0,149,0,149,0,149,0,149,0,149,0,149,0,149,0,149,0,149,0,149,0,149,0,149,0,149,0,149,0,149,0,149,0,1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16,17,18,19,20,21,22,23,24,25,26,27,28,29,30,31,32,33,34,35,36,37,38,39,40,41,42,43,44,45,46,47,48,49,50,51,52,53,54,55,56,57,58,59,60,61,62,63,64,65,66,67,68,69,70,71,72,73,74,75,76,77,78,79,80,81,82,83,84,85,86,87,88,89,90,91,92,93,94,95,96,97,98,99,100,101,102,103,104,105,106,107,108,109,110,111,112,113,114,115,116,117,118,119,120,121,122,123,124,125,126,127,128,129,130,131,132,133,134,135,136,137,138,139,140,141,142,143,144,145,146,147,148,149, 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,};
        uint8_t obstacle_y[800] = {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,1,2,2,3,3,4,4,5,5,6,6,7,7,8,8,9,9,10,10,11,11,12,12,13,13,14,14,15,15,16,16,17,17,18,18,19,19,20,20,21,21,22,22,23,23,24,24,25,25,26,26,26,26,26,26,26,26,26,26,26,26,27,27,27,27,28,28,28,28,29,29,29,29,30,30,30,30,31,31,31,31,32,32,32,32,33,33,33,33,34,34,34,34,35,35,35,35,36,36,36,36,36,36,36,36,36,36,36,36,37,37,38,38,39,39,40,40,41,41,41,41,41,41,41,41,41,41,41,41,42,42,42,42,43,43,43,43,44,44,44,44,45,45,45,45,46,46,46,46,47,47,47,47,48,48,48,48,49,49,49,49,50,50,50,50,50,50,50,50,50,50,50,50,51,51,52,52,53,53,54,54,55,55,56,56,57,57,58,58,59,59,60,60,61,61,62,62,63,63,64,64,65,65,66,66,67,67,68,68,69,69,70,70,71,71,72,72,73,73,74,74,75,75,76,76,77,77,78,78,79,79,80,80,81,81,82,82,82,82,82,82,82,82,82,82,82,82,83,83,83,83,84,84,84,84,85,85,85,85,86,86,86,86,86,86,86,86,86,86,86,86,86,86,87,87,87,87,87,87,88,88,88,88,88,88,89,89,89,89,89,89,90,90,90,90,90,90,91,91,91,91,91,91,91,91,91,91,91,91,91,91,92,92,92,92,93,93,93,93,94,94,94,94,95,95,95,95,95,95,95,95,95,95,95,95,96,96,97,97,97,97,97,97,97,97,97,97,97,97,98,98,98,98,99,99,99,99,100,100,100,100,101,101,101,101,102,102,102,102,103,103,103,103,104,104,104,104,105,105,105,105,106,106,106,106,106,106,106,106,106,106,106,106,107,107,108,108,109,109,110,110,111,111,112,112,113,113,114,114,115,115,116,116,117,117,118,118,119,119,120,120,121,121,122,122,123,123,124,124,125,125,126,126,127,127,128,128,129,129,130,130,131,131,132,132,133,133,134,134,135,135,136,136,137,137,138,138,139,139,140,140,141,141,142,142,143,143,144,144,145,145,146,146,147,147,148,148,149,149,149,149,149,149,149,149,149,149,149,149,149,149,149,149,149,149,149,149,149,149,149,149,149,149,149,149,149,149,149,149,149,149,149,149,149,149,149,149,149,149,149,149,149,149,149,149,149,149,149,149,149,149,149,149,149,149,149,149,149,149,149,149,149,149,149,149,149,149,149,149,149,149,149,149,149,149,149,149,149,149,149,149,149,149,149,149,149,149,149,149,149,149,149,149,149,149,149,149,149,149,149,149,149,149,149,149,149,149,149,149,149,149,149,149,149,149,149,149,149,149,149,149,149,149,149,149,149,149,149,149,149,149,149,149,149,149,149,149,149,149,149,149,149,149,149,149,149,149, 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,};
        uint8_t nb_scans = 0;
        int32_t min_distance = 0;
        uint16_t min_dist1 = 0;
        uint16_t min_dist2 = 0;
        uint16_t min_dist_final = 0;
        uint8_t oxi1 = 0;
        uint8_t oyi1 = 0;
        uint8_t oxi2 = 0;
        uint8_t oyi2 = 0;
        uint8_t oxi_final = 0;
        uint8_t oyi_final = 0;
        uint16_t min_distance_xy_index = 0;
        // uint16_t min_distance_y_index = 0;
        uint8_t particles_x[NUM_PARTICLES*9];
        uint8_t particles_y[NUM_PARTICLES*9];
        uint32_t inst;

        uint16_t i = 0;
        uint16_t i1 = 0;
        uint16_t particle_index = 0;

        while (istream.read(&inst))
        {
            uint16_t cmd = (inst >> 16) & 0xffff;
            if(cmd==0){
                // Read number of scans
                istream.read(&inst);
                nb_scans = inst & 0xff;
                // Read all particle positions
                for (i = 0; i < NUM_PARTICLES * nb_scans; i++)
                {
                    istream.read(&inst);
                    particles_x[i] = (inst >> 16) & 0xff;
                    particles_y[i] = (inst) & 0xff;
                }
                for(particle_index = 0; particle_index < NUM_PARTICLES * nb_scans; particle_index++){
                    min_distance = 0x7FFFFFFF;
                    int32_t px = particles_x[particle_index];
                    int32_t py = particles_y[particle_index];
                    _PIPELINE_
                    for (i1 = 0; i1 < 400; i1++){
                        int32_t ox1 = obstacle_x[i1];
                        int32_t oy1 = obstacle_y[i1];
                        int32_t ox2 = obstacle_x[i1+400];
                        int32_t oy2 = obstacle_y[i1+400];
                        // int32_t ox3 = obstacle_x[i1+400];
                        // int32_t oy3 = obstacle_y[i1+400];
                        // uint8_t ox4 = obstacle_x[i1+600];
                        // uint8_t oy4 = obstacle_y[i1+600];
                        int32_t distance_x1 = px - ox1;
                        int32_t distance_y1 = py - oy1;
                        int32_t distance_x2 = px - ox2;
                        int32_t distance_y2 = py - oy2;
                        // int32_t distance_x3 = px - ox3;
                        // int32_t distance_y3 = py - oy3;
                        // uint16_t distance_x4 = px - ox4;
                        // uint16_t distance_y4 = py - oy4;
                        int32_t distance1 = distance_x1 * distance_x1 + distance_y1 * distance_y1;
                        int32_t distance2 = distance_x2 * distance_x2 + distance_y2 * distance_y2;
                        // int32_t distance3 = distance_x3 * distance_x3 + distance_y3 * distance_y3;
                        // uint16_t distance4 = distance_x4 * distance_x4 + distance_y4 * distance_y4;
                        // if(distance1 < distance2){
                        //     min_dist1 = distance1;
                        //     oxi1 = ox1;
                        //     oyi1 = oy1;
                        // } else {
                        //     min_dist1 = distance2;
                        //     oxi1 = ox2;
                        //     oyi1 = oy2;
                        // }
                        // if (distance3 < distance4){
                        //     min_dist2 = distance3;
                        //     oxi2 = ox3;
                        //     oyi2 = oy3;
                        // } else {
                        //     min_dist2 = distance4;
                        //     oxi2 = ox4;
                        //     oyi2 = oy4;
                        // }
                        // if(min_dist1 < min_dist2){
                        //     min_dist_final = min_dist1;
                        //     oxi_final = oxi1;
                        //     oyi_final = oyi1;
                        // } else {
                        //     min_dist_final = min_dist2;
                        //     oxi_final = oxi2;
                        //     oyi_final = oyi2;
                        // }
                        // min_dist1 = MIN(distance1, distance2);
                        // min_dist2 = MIN(distance3, distance4);
                        int32_t min_dist_min = MIN(distance1, distance2);
                        if (min_dist_min < min_distance){
                            min_distance = min_dist_min;
                            // min_distance_xy_index = (oxi_final << 8) | oyi_final;
                        }
                    }
                    uint16_t dist = isqrt32(min_distance<<16);
                    ostream.write(dist);
                    // ostream.write(min_distance_xy_index);
                }
            }
        }
    }
};

int main(int argc, char *argv[])
{
    Upduino board;
    ParticleFilter filter;

    auto pipeline = board.serialIn >> filter >> board.serialOut;

    board.start(argc, argv);

    uint32_t instruction;

    uint16_t particles_x[NUM_PARTICLES] = {0};
    uint16_t particles_y[NUM_PARTICLES] = {0};
    uint16_t distances[NUM_PARTICLES] = {0};
    uint16_t indexesMsg[NUM_PARTICLES];
    uint16_t min_x[NUM_PARTICLES] = {0};
    uint16_t min_y[NUM_PARTICLES] = {0};

    // std::chrono::_V2::system_clock::time_point begin, end;
    // begin = std::chrono::high_resolution_clock::now();

    uint8_t NB_ITERATION = 100;
    for (int iteration = 0; iteration < NB_ITERATION; iteration++){
        // Send the particle position
        instruction = 0x00000000;
        pipeline.write(instruction);
        
        for (int i = 0; i < NUM_PARTICLES; i++)
        {
            instruction = (particles_x[i] << 16) | particles_y[i];
            pipeline.write(instruction);
        }
        // Read all particle data (don't print at the same time otherwise UART FIFO buffer has the time to overflow at higher number of particles)
        for (int i = 0; i < NUM_PARTICLES; i++)
        {
            pipeline.read(&(distances[i]));
            // pipeline.read(&(indexesMsg[i]));
        }
    }
    // end = std::chrono::high_resolution_clock::now();
    // for(int i = 0; i < NUM_PARTICLES; i++){
    //     printf("Particle %d: distance %d, min_x %d, min_y %d\n", i, distances[i], min_x[i], min_y[i]);
    // }
    // auto duration = std::chrono::duration_cast<std::chrono::nanoseconds>(end-begin).count();
    // std::cout << duration << "ns total, average : " << duration / NB_ITERATION << "ns." << std::endl;
}