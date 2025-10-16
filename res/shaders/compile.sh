#!/bin/bash
glslangValidator --target-env vulkan1.2 -D -S vert -e vertex UIRect.hlsl -o UIRect.vert.spv
glslangValidator --target-env vulkan1.2 -D -S frag -e fragment UIRect.hlsl -o UIRect.frag.spv
