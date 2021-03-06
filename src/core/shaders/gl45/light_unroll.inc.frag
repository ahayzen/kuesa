/*
    light_unroll.inc.frag

    This file is part of Kuesa.

    Copyright (C) 2018-2021 Klarälvdalens Datakonsult AB, a KDAB Group company, info@kdab.com
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

const int MAX_LIGHTS = 8;
const int TYPE_POINT = 0;
const int TYPE_DIRECTIONAL = 1;
const int TYPE_SPOT = 2;
struct Light {
    vec3 position;
    float intensity;
    vec3 color;
    float range;
    vec3 direction;
    float lightAngleScale;
    float lightAngleOffset;
    float shadowBias;
    int type;
    int depthArrayIndex;
    bool castsShadows;
    bool usePCF;
    mat4 lightProjectionMatrix;
    vec2 nearFarPlanes;
};

layout(std140, binding = auto) uniform LightBlock {
    Light light_0;
    Light light_1;
    Light light_2;
    Light light_3;
    Light light_4;
    Light light_5;
    Light light_6;
    Light light_7;
    int lightCount;
    int envLightCount;
};

// Pre-convolved environment maps
layout(binding = auto) uniform samplerCube envLightIrradiance; // For diffuse contribution
layout(binding = auto) uniform samplerCube envLightSpecular; // For specular contribution
