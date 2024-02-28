#version 330 core

precision highp float;

out vec4 fragmentColor;

in vec3 n_vec;
in vec3 v_vec;
in vec3 l_vec;
in float height;
in float bottom;
in vec2 tex_coord;

struct Material {
    vec3 ambient;
    vec3 diffuse;
    vec3 specular;
    float shininess;
};

uniform sampler2D grass_texture;
uniform sampler2D dirt_texture;
uniform sampler2D rock_texture;
uniform sampler2D snow_texture;

vec3 interpolateVector(float y, float limit1, float limit2, vec3 vector1, vec3 vector2) {
    float c = clamp(abs(y - limit1) / abs(limit2 - limit1), 0, 1);
    return mix(vector1, vector2, c);
}

const float rand_max = 10000;
float rand(float y) {
    return rand_max *
        sin(sqrt(abs(dot(vec2(y, 69), vec2(12.988, 78.233)))) * 4765.134);
}

void main() {	
     float snow_limit = bottom + 0.45f;
     float rock_limit = bottom + 0.3f;
     float dirt_limit = bottom + 0.1f;
     float grass_limit = bottom;

    vec3 grass_ambient = vec3(texture(grass_texture, tex_coord));
    const vec3 grass_diffuse = vec3(0.1, 0.1, 0.1);

    vec3 dirt_ambient = vec3(texture(dirt_texture, tex_coord));
    const vec3 dirt_diffuse = vec3(0.1, 0.1, 0.2);

    vec3 rock_ambient = vec3(texture(rock_texture, tex_coord));
    const vec3 rock_diffuse = vec3(0.2, 0.2, 0.2);

    vec3 snow_ambient = vec3(texture(snow_texture, tex_coord));
    const vec3 snow_diffuse = vec3(0.2, 0.2, 0.2);

    Material material;

    float r = rand(height) / rand_max / 10;
    if (height < dirt_limit) {
        material.ambient = interpolateVector(height, grass_limit, dirt_limit, grass_ambient, dirt_ambient);
        material.diffuse = interpolateVector(height, grass_limit, dirt_limit, grass_diffuse, dirt_diffuse);
        material.specular = vec3(0.1, 0.1, 0.0);
        material.shininess = 1;
    }
    else if (height < rock_limit) {
        material.ambient = interpolateVector(height, dirt_limit, rock_limit, dirt_ambient, rock_ambient);
        material.diffuse = interpolateVector(height, dirt_limit, rock_limit, dirt_diffuse, rock_diffuse);
        material.specular = vec3(0.1, 0.1, 0.0);
        material.shininess = 1;
    }
    else {
        material.ambient = interpolateVector(height, rock_limit, snow_limit, rock_ambient, snow_ambient);
        material.diffuse = interpolateVector(height, rock_limit, snow_limit, rock_diffuse, snow_diffuse);
        material.specular = vec3(0.1, 0.1, 0.0);
        material.shininess = 1;
    }

	vec3 h_vec = normalize(l_vec + v_vec);

    vec3 radiance = material.ambient;
    float lightCos = max(dot(n_vec, l_vec), 0);
    float viewCos = max(dot(n_vec, h_vec), 0);
    radiance += (material.diffuse * lightCos +
        material.specular * pow(viewCos, material.shininess));

	fragmentColor = vec4(radiance, 1);
}