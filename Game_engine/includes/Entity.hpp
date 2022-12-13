/*
** EPITECH PROJECT, 2022
** Entity.hpp
** File description:
** Game_engine
*/

#pragma once
#include "Component.hpp"

class Entity {
    public:
        Entity(const std::string name_entity);
        ~Entity();
        const std::string get_name_type();
        const bool get_ifcomp(const type_component &comp_e);
       
        /// @tparam
        
        template<typename component_t>
        void add_component(void *conf)
        {
            _list_component.push_back(new component_t(conf));
        }
        
        template<typename component_t>
        component_t *get_component(const type_component &comp_e)
        {
            for (int i = 0; i < _list_component.size(); i++) {
                if (_list_component[i]->get_type() == comp_e)
                    return static_cast<component_t *>(_list_component[i]);
            }
            throw std::logic_error("Don't find the component request");
        }

    protected:
    private:
        std::vector<AComponent *> _list_component; 
        std::string _name_entity;
};
