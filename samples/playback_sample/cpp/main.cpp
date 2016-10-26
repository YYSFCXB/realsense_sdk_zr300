// License: Apache 2.0. See LICENSE file in root directory.
// Copyright(c) 2016 Intel Corporation. All Rights Reserved.

#include <memory>
#include <iostream>
#include <vector>
#include <librealsense/rs.hpp>
#include "rs_sdk.h"
#include "unistd.h"

using namespace rs::core;
using namespace std;

int main(int argc, char* argv[])
{
    if (argc < 2)
    {
        cerr << "missing playback file argument" << endl;
        return -1;
    }
    if (access(argv[1], F_OK) == -1)
    {
        cerr << "playback file does not exists" << endl;
        return -1;
    }
    string playback_file_name(argv[1]);

    //create a playback enabled context with a given output file
    rs::playback::context context(playback_file_name.c_str());

    //get device count, in playback context there should be a single device.
    //in case device count is 0 there is probably problem with file location or permissions
    int device_count = context.get_device_count();
    if (device_count == 0)
    {
        cerr << "failed to open playback file" << endl;
        return -1;
    }

    //create a playback enabled device
    rs::device* device = context.get_device(0);

    //enable the recorded streams, for example, color and depth :
    vector<rs::stream> streams = { rs::stream::color, rs::stream::depth };

    try
    {
        for(auto iter = streams.begin(); iter != streams.end(); iter++)
        {
            if(device->get_stream_mode_count(*iter) > 0)
            {
                int width, height, fps;
                rs::format format;
                device->get_stream_mode(*iter, 0, width, height, format, fps);
                device->enable_stream(*iter, width, height, format, fps);
            }
        }

        device->start();

        //if theres no more frames the playback device will report that its not streaming
        while(device->is_streaming())
        {
            device->wait_for_frames();
            for(auto iter = streams.begin(); iter != streams.end(); iter++)
            {
                if(device->is_stream_enabled(*iter))
                {
                    auto frame_data = device->get_frame_data(*iter);

                    //use the recorded frame...
                }
            }
        }
        device->stop();
    }

    catch(rs::error e)
    {
        std::cout << e.what() << std::endl;
        return -1;
    }

    return 0;
}

