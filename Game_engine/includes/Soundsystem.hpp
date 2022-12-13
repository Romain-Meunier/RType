/*
** EPITECH PROJECT, 2022
** soundsystem.hpp
** File description:
** System
*/

#pragma once

#include "Entity.hpp"

class Game_engine;

class I_Soundsystem {
    public:
        virtual ~I_Soundsystem() = default;
        virtual std::vector<std::pair<Sound_impl *, std::string>> &get_sound() = 0;
        virtual void running_music() = 0;
        virtual void play_sound_effect() = 0;
        virtual void start_playlist() = 0;
        virtual void add_music(const std::string &path_music, const std::string &name_music) = 0;
        virtual void del_music(const std::string &name_music) = 0;
        virtual void add_sound_effect(const std::string &path_music) = 0;
        virtual void clear_sound_effect() = 0;
    protected:
    private:
};

class Soundsystem : public I_Soundsystem {
    public:
        Soundsystem(void *conf = nullptr);
        ~Soundsystem() final;
        std::vector<std::pair<Sound_impl *, std::string>> &get_sound() final;
        void running_music() final;
        void play_sound_effect() final;
        void start_playlist() final;
        void add_music(const std::string &path_music, const std::string &name_music) final;
        void del_music(const std::string &name_music) final;
        void add_sound_effect(const std::string &path_music);
        void clear_sound_effect() final;
    protected:
        std::vector<std::pair<Sound_impl *, std::string>> _lib_music;
        std::vector<Sound_impl *> _lib_sound_effect;
        unsigned int _index_music;
    private:
};