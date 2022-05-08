-- name: Audio Test
-- description: audio shits.
-- incompatible:

DEBUG = false
UNST22 = true -- gotta work around unst 22 bugs :(

-------------------------------------------------------------------------------

handle = 0;
s_handle = 0;

function on_audio_play(msg)
    if(msg == "create") then
        handle = load_audio("test.mp3")

        djui_chat_message_create("audio handle:" .. tostring(handle));
    end

    if(msg == "play") then
        play_audio(handle, true);
        djui_chat_message_create("playing audio");
    end

    if(msg == "resume") then
        play_audio(handle, false);
        djui_chat_message_create("resuming audio");
    end

    if(msg == "pause") then
        pause_audio(handle);
        djui_chat_message_create("pausing audio");
    end

    if(msg == "stop") then
        stop_audio(handle);
        djui_chat_message_create("stopping audio");
    end

    if(msg == "destroy") then
        destroy_audio(handle);
        djui_chat_message_create("destroyed audio");
    end

    if(msg == "getpos") then
        djui_chat_message_create("pos: " .. tostring(get_position_audio(handle)));
    end

    return true;
end

function on_sample_play(msg)
    if(msg == "create") then
        s_handle = load_sample("test.mp3");

        djui_chat_message_create("audio handle:" .. tostring(s_handle));

        return true;
    end

    handle2 = get_audio_from_sample(s_handle);

    play_audio(handle2, false);
    return true;
end

hook_chat_command('audio', "options and shit", on_audio_play)
hook_chat_command('sample', "options and shit", on_sample_play)
