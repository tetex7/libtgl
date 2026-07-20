/*
 * Copyright (c) 2026. Tetex7
 *
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this
 * file, You can obtain one at https://mozilla.org/MPL/2.0/.
 */

//
// Created by tete on 07/18/2026.
//

#ifndef LIBTGL_INIOBJECT_HPP
#define LIBTGL_INIOBJECT_HPP
#include <tgl/Object.hpp>
#include <tgl/ini/IniField.hpp>
#include <map>


namespace tgl::ini
{
    class IniObject : public Object
    {
        std::map<IniIdentifier, IniField> contents;

    public:
        IniObject() = default;

        void set(const IniIdentifier& name, IniField& value);

        template <isIniObjectConpat T>
        ini_field_type_selector_t<T> get(const IniIdentifier& name)
        {
            return contents[name];
        }

        ~IniObject() override = default;
    };
}

#endif //LIBTGL_INIOBJECT_HPP
