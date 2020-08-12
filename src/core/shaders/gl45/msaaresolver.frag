#version 450 core

/*
    msaaresolver.frag

    This file is part of Kuesa.

    Copyright (C) 2018-2020 Klarälvdalens Datakonsult AB, a KDAB Group company, info@kdab.com
    Author: Paul Lemire <paul.lemire@kdab.com>

    Licensees holding valid proprietary KDAB Kuesa licenses may use this file in
    accordance with the Kuesa Enterprise License Agreement provided with the Software in the
    LICENSE.KUESA.ENTERPRISE file.

    Contact info@kdab.com if any conditions of this licensing are not clear to you.

    This program is free software: you can redistribute it and/or modify
    it under the terms of the GNU Affero General Public License as
    published by the Free Software Foundation, either version 3 of the
    License, or (at your option) any later version.

    This program is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU Affero General Public License for more details.

    You should have received a copy of the GNU Affero General Public License
    along with this program.  If not, see <https://www.gnu.org/licenses/>.
*/

layout(binding=0) uniform sampler2DMS source;

layout(location = 0) in vec2 texCoord;
layout(location = 0) out vec4 fragColor;

void main()
{
    ivec2 s = textureSize(source);
    ivec2 t = ivec2(floor(vec2(s)) * texCoord);
    vec4 sample1 = texelFetch(source, t, 0);
    vec4 sample2 = texelFetch(source, t, 1);
    vec4 sample3 = texelFetch(source, t, 2);
    vec4 sample4 = texelFetch(source, t, 3);

    fragColor = (sample1 + sample2 + sample3 + sample4) * 0.25;
}
