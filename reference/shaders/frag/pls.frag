#version 310 es
precision mediump float;
precision highp int;

layout(location = 0) out vec4 PLSOut0;
layout(location = 0) in vec4 PLSIn0;
layout(location = 1) out vec4 PLSOut1;
layout(location = 1) in vec4 PLSIn1;
layout(location = 2) out vec4 PLSOut2;
in vec4 PLSIn2;
layout(location = 3) out vec4 PLSOut3;
in vec4 PLSIn3;

void main()
{
    PLSOut0 = (PLSIn0 * 2.000000);
    PLSOut1 = (PLSIn1 * 6.000000);
    PLSOut2 = (PLSIn2 * 7.000000);
    PLSOut3 = (PLSIn3 * 4.000000);
}

