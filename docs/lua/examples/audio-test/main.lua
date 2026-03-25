-- name: Audio Test
-- description: Testing out the custom audio system
-- incompatible:

audioStream = nil;
audioSample = nil;

function on_stream_play(msg)
    if(msg == "load") then
        audioStream = audio_stream_load("music.mp3")
        audio_stream_set_looping(audioStream, true)
        command_message_create("audio audioStream:" .. tostring(audioStream));
    end

    if(msg == "play") then
        audio_stream_play(audioStream, true, 1);
        command_message_create("playing audio");
    end

    if(msg == "resume") then
        audio_stream_play(audioStream, false, 1);
        command_message_create("resuming audio");
    end

    if(msg == "pause") then
        audio_stream_pause(audioStream);
        command_message_create("pausing audio");
    end

    if(msg == "stop") then
        audio_stream_stop(audioStream);
        command_message_create("stopping audio");
    end

    if(msg == "destroy") then
        audio_stream_destroy(audioStream);
        command_message_create("destroyed audio");
    end

    if(msg == "getpos") then
        command_message_create("pos: " .. tostring(audio_stream_get_position(audioStream)));
    end

    return true;
end

function on_sample_play(msg)
    if(msg == "load") then
        audioSample = audio_sample_load("sample.mp3");

        command_message_create("audio audioStream:" .. tostring(audioSample));

        return true;
    end

    audio_sample_play(audioSample, gMarioStates[0].pos, 1);
    return true;
end

hook_chat_command('stream', "[load|play|resume|pause|stop|destroy|getpos]", on_stream_play)
hook_chat_command('sample', "[load|play]", on_sample_play)
