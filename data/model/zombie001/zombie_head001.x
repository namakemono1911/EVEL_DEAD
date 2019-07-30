xof 0302txt 0064
template Header {
 <3D82AB43-62DA-11cf-AB39-0020AF71E433>
 WORD major;
 WORD minor;
 DWORD flags;
}

template Vector {
 <3D82AB5E-62DA-11cf-AB39-0020AF71E433>
 FLOAT x;
 FLOAT y;
 FLOAT z;
}

template Coords2d {
 <F6F23F44-7686-11cf-8F52-0040333594A3>
 FLOAT u;
 FLOAT v;
}

template Matrix4x4 {
 <F6F23F45-7686-11cf-8F52-0040333594A3>
 array FLOAT matrix[16];
}

template ColorRGBA {
 <35FF44E0-6C7C-11cf-8F52-0040333594A3>
 FLOAT red;
 FLOAT green;
 FLOAT blue;
 FLOAT alpha;
}

template ColorRGB {
 <D3E16E81-7835-11cf-8F52-0040333594A3>
 FLOAT red;
 FLOAT green;
 FLOAT blue;
}

template IndexedColor {
 <1630B820-7842-11cf-8F52-0040333594A3>
 DWORD index;
 ColorRGBA indexColor;
}

template Boolean {
 <4885AE61-78E8-11cf-8F52-0040333594A3>
 WORD truefalse;
}

template Boolean2d {
 <4885AE63-78E8-11cf-8F52-0040333594A3>
 Boolean u;
 Boolean v;
}

template MaterialWrap {
 <4885AE60-78E8-11cf-8F52-0040333594A3>
 Boolean u;
 Boolean v;
}

template TextureFilename {
 <A42790E1-7810-11cf-8F52-0040333594A3>
 STRING filename;
}

template Material {
 <3D82AB4D-62DA-11cf-AB39-0020AF71E433>
 ColorRGBA faceColor;
 FLOAT power;
 ColorRGB specularColor;
 ColorRGB emissiveColor;
 [...]
}

template MeshFace {
 <3D82AB5F-62DA-11cf-AB39-0020AF71E433>
 DWORD nFaceVertexIndices;
 array DWORD faceVertexIndices[nFaceVertexIndices];
}

template MeshFaceWraps {
 <4885AE62-78E8-11cf-8F52-0040333594A3>
 DWORD nFaceWrapValues;
 Boolean2d faceWrapValues;
}

template MeshTextureCoords {
 <F6F23F40-7686-11cf-8F52-0040333594A3>
 DWORD nTextureCoords;
 array Coords2d textureCoords[nTextureCoords];
}

template MeshMaterialList {
 <F6F23F42-7686-11cf-8F52-0040333594A3>
 DWORD nMaterials;
 DWORD nFaceIndexes;
 array DWORD faceIndexes[nFaceIndexes];
 [Material]
}

template MeshNormals {
 <F6F23F43-7686-11cf-8F52-0040333594A3>
 DWORD nNormals;
 array Vector normals[nNormals];
 DWORD nFaceNormals;
 array MeshFace faceNormals[nFaceNormals];
}

template MeshVertexColors {
 <1630B821-7842-11cf-8F52-0040333594A3>
 DWORD nVertexColors;
 array IndexedColor vertexColors[nVertexColors];
}

template Mesh {
 <3D82AB44-62DA-11cf-AB39-0020AF71E433>
 DWORD nVertices;
 array Vector vertices[nVertices];
 DWORD nFaces;
 array MeshFace faces[nFaces];
 [...]
}

Header{
1;
0;
1;
}

Mesh {
 254;
 0.00000;3.98656;0.00000;,
 -0.16913;3.94286;-0.37987;,
 0.00000;3.94286;-0.41582;,
 0.00000;3.98656;0.00000;,
 -0.30902;3.94286;-0.27824;,
 0.00000;3.98656;0.00000;,
 -0.39547;3.94286;-0.12850;,
 0.00000;3.98656;0.00000;,
 -0.41355;3.94286;0.04347;,
 0.00000;3.98656;0.00000;,
 -0.36011;3.94286;0.20791;,
 0.00000;3.98656;0.00000;,
 -0.24441;3.94286;0.33641;,
 0.00000;3.98656;0.00000;,
 -0.08645;3.94286;0.40674;,
 0.00000;3.98656;0.00000;,
 0.08645;3.94286;0.40674;,
 0.00000;3.98656;0.00000;,
 0.24441;3.94286;0.33641;,
 0.00000;3.98656;0.00000;,
 0.36011;3.94286;0.20791;,
 0.00000;3.98656;0.00000;,
 0.41355;3.94286;0.04347;,
 0.00000;3.98656;0.00000;,
 0.39547;3.94286;-0.12850;,
 0.00000;3.98656;0.00000;,
 0.30902;3.94286;-0.27824;,
 0.00000;3.98656;0.00000;,
 0.16913;3.94286;-0.37987;,
 0.00000;3.98656;0.00000;,
 0.00000;3.94286;-0.41582;,
 -0.33087;3.81365;-0.74314;,
 0.00000;3.81365;-0.81347;,
 -0.60453;3.81365;-0.54432;,
 -0.77366;3.81365;-0.25138;,
 -0.80902;3.81365;0.08503;,
 -0.70449;3.81365;0.40674;,
 -0.47815;3.81365;0.65811;,
 -0.16913;3.81365;0.79570;,
 0.16913;3.81365;0.79570;,
 0.47815;3.81365;0.65811;,
 0.70449;3.81365;0.40674;,
 0.80902;3.81365;0.08503;,
 0.77366;3.81365;-0.25138;,
 0.60453;3.81365;-0.54432;,
 0.33087;3.81365;-0.74314;,
 0.00000;3.81365;-0.81347;,
 -0.47815;3.60460;-1.07394;,
 0.00000;3.60460;-1.17557;,
 -0.87362;3.60460;-0.78661;,
 -1.11803;3.60460;-0.36327;,
 -1.16913;3.60460;0.12288;,
 -1.01807;3.60460;0.58779;,
 -0.69098;3.60460;0.95106;,
 -0.24441;3.60460;1.14988;,
 0.24441;3.60460;1.14988;,
 0.69098;3.60460;0.95106;,
 1.01807;3.60460;0.58779;,
 1.16913;3.60460;0.12288;,
 1.11803;3.60460;-0.36327;,
 0.87362;3.60460;-0.78661;,
 0.47815;3.60460;-1.07394;,
 0.00000;3.60460;-1.17557;,
 -0.60453;3.32482;-1.35779;,
 0.00000;3.32482;-1.48629;,
 -1.10453;3.32482;-0.99452;,
 -1.41355;3.32482;-0.45929;,
 -1.47815;3.32482;0.15536;,
 -1.28716;3.32482;0.74314;,
 -0.87362;3.32482;1.20243;,
 -0.30902;3.32482;1.45381;,
 0.30902;3.32482;1.45381;,
 0.87362;3.32482;1.20243;,
 1.28716;3.32482;0.74314;,
 1.47815;3.32482;0.15536;,
 1.41355;3.32482;-0.45929;,
 1.10453;3.32482;-0.99452;,
 0.60453;3.32482;-1.35779;,
 0.00000;3.32482;-1.48629;,
 -0.70449;2.98656;-1.58231;,
 0.00000;2.98656;-1.73205;,
 -1.28716;2.98656;-1.15897;,
 -1.64728;2.98656;-0.53523;,
 -1.72256;2.98656;0.18105;,
 -1.50000;2.98656;0.86603;,
 -1.01807;2.98656;1.40126;,
 -0.36011;2.98656;1.69420;,
 0.36011;2.98656;1.69420;,
 1.01807;2.98656;1.40126;,
 1.50000;2.98656;0.86603;,
 1.72256;2.98656;0.18105;,
 1.64728;2.98656;-0.53523;,
 1.28716;2.98656;-1.15897;,
 0.70449;2.98656;-1.58231;,
 0.00000;2.98656;-1.73205;,
 -0.77366;2.60459;-1.73767;,
 0.00000;2.60459;-1.90211;,
 -1.41355;2.60459;-1.27276;,
 -1.80902;2.60459;-0.58779;,
 -1.89169;2.60459;0.19883;,
 -1.64728;2.60459;0.95106;,
 -1.11803;2.60459;1.53884;,
 -0.39547;2.60459;1.86055;,
 0.39547;2.60459;1.86055;,
 1.11803;2.60459;1.53884;,
 1.64728;2.60459;0.95106;,
 1.89169;2.60459;0.19882;,
 1.80902;2.60459;-0.58779;,
 1.41355;2.60459;-1.27276;,
 0.77366;2.60459;-1.73767;,
 0.00000;2.60459;-1.90211;,
 -0.80902;2.19562;-1.81708;,
 0.00000;2.19562;-1.98904;,
 -1.47815;2.19562;-1.33093;,
 -1.89169;2.19562;-0.61465;,
 -1.97815;2.19562;0.20791;,
 -1.72256;2.19562;0.99452;,
 -1.16913;2.19562;1.60917;,
 -0.41355;2.19562;1.94558;,
 0.41355;2.19562;1.94558;,
 1.16913;2.19562;1.60917;,
 1.72256;2.19562;0.99452;,
 1.97815;2.19562;0.20791;,
 1.89169;2.19562;-0.61465;,
 1.47815;2.19562;-1.33093;,
 0.80902;2.19562;-1.81708;,
 0.00000;2.19562;-1.98904;,
 -0.80902;1.77750;-1.81708;,
 0.00000;1.77750;-1.98904;,
 -1.47815;1.77750;-1.33093;,
 -1.89169;1.77750;-0.61465;,
 -1.97815;1.77750;0.20791;,
 -1.72256;1.77750;0.99452;,
 -1.16913;1.77750;1.60917;,
 -0.41355;1.77750;1.94558;,
 0.41355;1.77750;1.94558;,
 1.16913;1.77750;1.60917;,
 1.72256;1.77750;0.99452;,
 1.97815;1.77750;0.20791;,
 1.89169;1.77750;-0.61465;,
 1.47815;1.77750;-1.33093;,
 0.80902;1.77750;-1.81708;,
 0.00000;1.77750;-1.98904;,
 -0.77366;1.36853;-1.73767;,
 0.00000;1.36853;-1.90211;,
 -1.41355;1.36853;-1.27276;,
 -1.80902;1.36853;-0.58779;,
 -1.89169;1.36853;0.19883;,
 -1.64728;1.36853;0.95106;,
 -1.11803;1.36853;1.53884;,
 -0.39547;1.36853;1.86055;,
 0.39547;1.36853;1.86055;,
 1.11803;1.36853;1.53884;,
 1.64728;1.36853;0.95106;,
 1.89169;1.36853;0.19882;,
 1.80902;1.36853;-0.58779;,
 1.41355;1.36853;-1.27276;,
 0.77366;1.36853;-1.73767;,
 0.00000;1.36853;-1.90211;,
 -0.70449;0.98656;-1.58231;,
 0.00000;0.98656;-1.73205;,
 -1.28716;0.98656;-1.15897;,
 -1.64728;0.98656;-0.53523;,
 -1.72256;0.98656;0.18105;,
 -1.50000;0.98656;0.86603;,
 -1.01807;0.98656;1.40126;,
 -0.36011;0.98656;1.69420;,
 0.36011;0.98656;1.69420;,
 1.01807;0.98656;1.40126;,
 1.50000;0.98656;0.86603;,
 1.72256;0.98656;0.18105;,
 1.64728;0.98656;-0.53523;,
 1.28716;0.98656;-1.15897;,
 0.70449;0.98656;-1.58231;,
 0.00000;0.98656;-1.73205;,
 -0.60453;0.64830;-1.35779;,
 0.00000;0.64830;-1.48629;,
 -1.10453;0.64830;-0.99452;,
 -1.41355;0.64830;-0.45929;,
 -1.47815;0.64830;0.15536;,
 -1.28716;0.64830;0.74314;,
 -0.87362;0.64830;1.20243;,
 -0.30902;0.64830;1.45381;,
 0.30902;0.64830;1.45381;,
 0.87362;0.64830;1.20243;,
 1.28716;0.64830;0.74314;,
 1.47815;0.64830;0.15536;,
 1.41355;0.64830;-0.45929;,
 1.10453;0.64830;-0.99452;,
 0.60453;0.64830;-1.35779;,
 0.00000;0.64830;-1.48629;,
 -0.47815;0.36853;-1.07394;,
 0.00000;0.36853;-1.17557;,
 -0.87362;0.36853;-0.78661;,
 -1.11803;0.36853;-0.36327;,
 -1.16913;0.36853;0.12288;,
 -1.01807;0.36853;0.58779;,
 -0.69098;0.36853;0.95106;,
 -0.24441;0.36853;1.14988;,
 0.24441;0.36853;1.14988;,
 0.69098;0.36853;0.95106;,
 1.01807;0.36853;0.58779;,
 1.16913;0.36853;0.12288;,
 1.11803;0.36853;-0.36327;,
 0.87362;0.36853;-0.78661;,
 0.47815;0.36853;-1.07394;,
 0.00000;0.36853;-1.17557;,
 -0.33087;0.15947;-0.74314;,
 0.00000;0.15947;-0.81347;,
 -0.60453;0.15947;-0.54432;,
 -0.77366;0.15947;-0.25138;,
 -0.80902;0.15947;0.08503;,
 -0.70449;0.15947;0.40674;,
 -0.47815;0.15947;0.65811;,
 -0.16913;0.15947;0.79570;,
 0.16913;0.15947;0.79570;,
 0.47815;0.15947;0.65811;,
 0.70449;0.15947;0.40674;,
 0.80902;0.15947;0.08503;,
 0.77366;0.15947;-0.25138;,
 0.60453;0.15947;-0.54432;,
 0.33087;0.15947;-0.74314;,
 0.00000;0.15947;-0.81347;,
 -0.16913;0.03026;-0.37987;,
 0.00000;0.03026;-0.41582;,
 -0.30902;0.03026;-0.27824;,
 -0.39547;0.03026;-0.12850;,
 -0.41355;0.03026;0.04347;,
 -0.36011;0.03026;0.20791;,
 -0.24441;0.03026;0.33641;,
 -0.08645;0.03026;0.40674;,
 0.08645;0.03026;0.40674;,
 0.24441;0.03026;0.33641;,
 0.36011;0.03026;0.20791;,
 0.41355;0.03026;0.04347;,
 0.39547;0.03026;-0.12850;,
 0.30902;0.03026;-0.27824;,
 0.16913;0.03026;-0.37987;,
 0.00000;0.03026;-0.41582;,
 0.00000;-0.01344;0.00000;,
 0.00000;-0.01344;0.00000;,
 0.00000;-0.01344;0.00000;,
 0.00000;-0.01344;0.00000;,
 0.00000;-0.01344;0.00000;,
 0.00000;-0.01344;0.00000;,
 0.00000;-0.01344;0.00000;,
 0.00000;-0.01344;0.00000;,
 0.00000;-0.01344;0.00000;,
 0.00000;-0.01344;0.00000;,
 0.00000;-0.01344;0.00000;,
 0.00000;-0.01344;0.00000;,
 0.00000;-0.01344;0.00000;,
 0.00000;-0.01344;0.00000;,
 0.00000;-0.01344;0.00000;;
 
 225;
 3;2,1,0;,
 3;1,4,3;,
 3;4,6,5;,
 3;6,8,7;,
 3;8,10,9;,
 3;10,12,11;,
 3;12,14,13;,
 3;14,16,15;,
 3;16,18,17;,
 3;18,20,19;,
 3;20,22,21;,
 3;22,24,23;,
 3;24,26,25;,
 3;26,28,27;,
 3;28,30,29;,
 4;32,31,1,2;,
 4;31,33,4,1;,
 4;33,34,6,4;,
 4;34,35,8,6;,
 4;35,36,10,8;,
 4;36,37,12,10;,
 4;37,38,14,12;,
 4;38,39,16,14;,
 4;39,40,18,16;,
 4;40,41,20,18;,
 4;41,42,22,20;,
 4;42,43,24,22;,
 4;43,44,26,24;,
 4;44,45,28,26;,
 4;45,46,30,28;,
 4;48,47,31,32;,
 4;47,49,33,31;,
 4;49,50,34,33;,
 4;50,51,35,34;,
 4;51,52,36,35;,
 4;52,53,37,36;,
 4;53,54,38,37;,
 4;54,55,39,38;,
 4;55,56,40,39;,
 4;56,57,41,40;,
 4;57,58,42,41;,
 4;58,59,43,42;,
 4;59,60,44,43;,
 4;60,61,45,44;,
 4;61,62,46,45;,
 4;64,63,47,48;,
 4;63,65,49,47;,
 4;65,66,50,49;,
 4;66,67,51,50;,
 4;67,68,52,51;,
 4;68,69,53,52;,
 4;69,70,54,53;,
 4;70,71,55,54;,
 4;71,72,56,55;,
 4;72,73,57,56;,
 4;73,74,58,57;,
 4;74,75,59,58;,
 4;75,76,60,59;,
 4;76,77,61,60;,
 4;77,78,62,61;,
 4;80,79,63,64;,
 4;79,81,65,63;,
 4;81,82,66,65;,
 4;82,83,67,66;,
 4;83,84,68,67;,
 4;84,85,69,68;,
 4;85,86,70,69;,
 4;86,87,71,70;,
 4;87,88,72,71;,
 4;88,89,73,72;,
 4;89,90,74,73;,
 4;90,91,75,74;,
 4;91,92,76,75;,
 4;92,93,77,76;,
 4;93,94,78,77;,
 4;96,95,79,80;,
 4;95,97,81,79;,
 4;97,98,82,81;,
 4;98,99,83,82;,
 4;99,100,84,83;,
 4;100,101,85,84;,
 4;101,102,86,85;,
 4;102,103,87,86;,
 4;103,104,88,87;,
 4;104,105,89,88;,
 4;105,106,90,89;,
 4;106,107,91,90;,
 4;107,108,92,91;,
 4;108,109,93,92;,
 4;109,110,94,93;,
 4;112,111,95,96;,
 4;111,113,97,95;,
 4;113,114,98,97;,
 4;114,115,99,98;,
 4;115,116,100,99;,
 4;116,117,101,100;,
 4;117,118,102,101;,
 4;118,119,103,102;,
 4;119,120,104,103;,
 4;120,121,105,104;,
 4;121,122,106,105;,
 4;122,123,107,106;,
 4;123,124,108,107;,
 4;124,125,109,108;,
 4;125,126,110,109;,
 4;128,127,111,112;,
 4;127,129,113,111;,
 4;129,130,114,113;,
 4;130,131,115,114;,
 4;131,132,116,115;,
 4;132,133,117,116;,
 4;133,134,118,117;,
 4;134,135,119,118;,
 4;135,136,120,119;,
 4;136,137,121,120;,
 4;137,138,122,121;,
 4;138,139,123,122;,
 4;139,140,124,123;,
 4;140,141,125,124;,
 4;141,142,126,125;,
 4;144,143,127,128;,
 4;143,145,129,127;,
 4;145,146,130,129;,
 4;146,147,131,130;,
 4;147,148,132,131;,
 4;148,149,133,132;,
 4;149,150,134,133;,
 4;150,151,135,134;,
 4;151,152,136,135;,
 4;152,153,137,136;,
 4;153,154,138,137;,
 4;154,155,139,138;,
 4;155,156,140,139;,
 4;156,157,141,140;,
 4;157,158,142,141;,
 4;160,159,143,144;,
 4;159,161,145,143;,
 4;161,162,146,145;,
 4;162,163,147,146;,
 4;163,164,148,147;,
 4;164,165,149,148;,
 4;165,166,150,149;,
 4;166,167,151,150;,
 4;167,168,152,151;,
 4;168,169,153,152;,
 4;169,170,154,153;,
 4;170,171,155,154;,
 4;171,172,156,155;,
 4;172,173,157,156;,
 4;173,174,158,157;,
 4;176,175,159,160;,
 4;175,177,161,159;,
 4;177,178,162,161;,
 4;178,179,163,162;,
 4;179,180,164,163;,
 4;180,181,165,164;,
 4;181,182,166,165;,
 4;182,183,167,166;,
 4;183,184,168,167;,
 4;184,185,169,168;,
 4;185,186,170,169;,
 4;186,187,171,170;,
 4;187,188,172,171;,
 4;188,189,173,172;,
 4;189,190,174,173;,
 4;192,191,175,176;,
 4;191,193,177,175;,
 4;193,194,178,177;,
 4;194,195,179,178;,
 4;195,196,180,179;,
 4;196,197,181,180;,
 4;197,198,182,181;,
 4;198,199,183,182;,
 4;199,200,184,183;,
 4;200,201,185,184;,
 4;201,202,186,185;,
 4;202,203,187,186;,
 4;203,204,188,187;,
 4;204,205,189,188;,
 4;205,206,190,189;,
 4;208,207,191,192;,
 4;207,209,193,191;,
 4;209,210,194,193;,
 4;210,211,195,194;,
 4;211,212,196,195;,
 4;212,213,197,196;,
 4;213,214,198,197;,
 4;214,215,199,198;,
 4;215,216,200,199;,
 4;216,217,201,200;,
 4;217,218,202,201;,
 4;218,219,203,202;,
 4;219,220,204,203;,
 4;220,221,205,204;,
 4;221,222,206,205;,
 4;224,223,207,208;,
 4;223,225,209,207;,
 4;225,226,210,209;,
 4;226,227,211,210;,
 4;227,228,212,211;,
 4;228,229,213,212;,
 4;229,230,214,213;,
 4;230,231,215,214;,
 4;231,232,216,215;,
 4;232,233,217,216;,
 4;233,234,218,217;,
 4;234,235,219,218;,
 4;235,236,220,219;,
 4;236,237,221,220;,
 4;237,238,222,221;,
 3;239,223,224;,
 3;240,225,223;,
 3;241,226,225;,
 3;242,227,226;,
 3;243,228,227;,
 3;244,229,228;,
 3;245,230,229;,
 3;246,231,230;,
 3;247,232,231;,
 3;248,233,232;,
 3;249,234,233;,
 3;250,235,234;,
 3;251,236,235;,
 3;252,237,236;,
 3;253,238,237;;
 
 MeshMaterialList {
  4;
  225;
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0;;
  Material {
   0.800000;0.664800;0.429600;1.000000;;
   5.000000;
   0.000000;0.000000;0.000000;;
   0.000000;0.000000;0.000000;;
  }
  Material {
   0.800000;0.034400;0.106400;1.000000;;
   5.000000;
   0.000000;0.000000;0.000000;;
   0.000000;0.000000;0.000000;;
  }
  Material {
   0.116000;0.254400;0.800000;1.000000;;
   5.000000;
   0.000000;0.000000;0.000000;;
   0.000000;0.000000;0.000000;;
  }
  Material {
   0.458400;0.460800;0.423200;1.000000;;
   5.000000;
   0.000000;0.000000;0.000000;;
   0.000000;0.000000;0.000000;;
  }
 }
 MeshNormals {
  212;
  -0.000000;1.000000;-0.000000;,
  0.000000;0.978168;-0.207816;,
  -0.084525;0.978168;-0.189851;,
  -0.154436;0.978168;-0.139057;,
  -0.197644;0.978168;-0.064220;,
  -0.206676;0.978168;0.021724;,
  -0.179972;0.978168;0.103911;,
  -0.122152;0.978168;0.168126;,
  -0.043208;0.978168;0.203274;,
  0.043208;0.978168;0.203274;,
  0.122152;0.978168;0.168126;,
  0.179972;0.978168;0.103911;,
  0.206676;0.978168;0.021724;,
  0.197644;0.978168;-0.064220;,
  0.154436;0.978168;-0.139057;,
  0.084525;0.978168;-0.189851;,
  0.000000;0.913621;-0.406567;,
  -0.165364;0.913621;-0.371419;,
  -0.302139;0.913620;-0.272048;,
  -0.386673;0.913619;-0.125639;,
  -0.404344;0.913619;0.042499;,
  -0.352099;0.913619;0.203288;,
  -0.238976;0.913619;0.328922;,
  -0.084532;0.913619;0.397686;,
  0.084532;0.913619;0.397687;,
  0.238976;0.913619;0.328922;,
  0.352099;0.913619;0.203288;,
  0.404344;0.913619;0.042499;,
  0.386673;0.913619;-0.125639;,
  0.302139;0.913620;-0.272048;,
  0.165364;0.913621;-0.371419;,
  0.000000;0.809154;-0.587597;,
  -0.238997;0.809154;-0.536797;,
  -0.436670;0.809154;-0.393178;,
  -0.558837;0.809154;-0.181578;,
  -0.584378;0.809154;0.061421;,
  -0.508876;0.809151;0.293802;,
  -0.345382;0.809152;0.475378;,
  -0.122168;0.809153;0.574758;,
  0.122168;0.809153;0.574758;,
  0.345382;0.809152;0.475378;,
  0.508876;0.809151;0.293802;,
  0.584378;0.809154;0.061421;,
  0.558837;0.809154;-0.181578;,
  0.436670;0.809154;-0.393178;,
  0.238997;0.809154;-0.536797;,
  0.000000;0.669305;-0.742988;,
  -0.302201;0.669305;-0.678753;,
  -0.552148;0.669304;-0.497156;,
  -0.706623;0.669305;-0.229596;,
  -0.738916;0.669306;0.077666;,
  -0.643445;0.669306;0.371495;,
  -0.436718;0.669305;0.601089;,
  -0.154476;0.669304;0.726752;,
  0.154476;0.669304;0.726752;,
  0.436718;0.669305;0.601089;,
  0.643445;0.669306;0.371495;,
  0.738916;0.669306;0.077666;,
  0.706623;0.669305;-0.229596;,
  0.552148;0.669304;-0.497156;,
  0.302201;0.669305;-0.678753;,
  0.000000;0.500179;-0.865922;,
  -0.352202;0.500180;-0.791058;,
  -0.643505;0.500180;-0.579415;,
  -0.823542;0.500178;-0.267584;,
  -0.861179;0.500178;0.090516;,
  -0.749909;0.500181;0.432962;,
  -0.508975;0.500180;0.700546;,
  -0.180036;0.500180;0.846999;,
  0.180036;0.500180;0.846999;,
  0.508975;0.500180;0.700546;,
  0.749909;0.500181;0.432961;,
  0.861179;0.500177;0.090515;,
  0.823542;0.500178;-0.267584;,
  0.643505;0.500180;-0.579415;,
  0.352202;0.500180;-0.791058;,
  0.000000;0.309145;-0.951015;,
  -0.386811;0.309147;-0.868795;,
  -0.706741;0.309150;-0.636352;,
  -0.904468;0.309150;-0.293878;,
  -0.945804;0.309149;0.099409;,
  -0.823601;0.309148;0.475509;,
  -0.558991;0.309149;0.769387;,
  -0.197728;0.309152;0.930230;,
  0.197728;0.309152;0.930230;,
  0.558991;0.309149;0.769387;,
  0.823602;0.309148;0.475508;,
  0.945804;0.309149;0.099408;,
  0.904468;0.309150;-0.293878;,
  0.706741;0.309150;-0.636352;,
  0.386811;0.309147;-0.868795;,
  0.000000;0.104576;-0.994517;,
  -0.404504;0.104577;-0.908537;,
  -0.739071;0.104576;-0.665461;,
  -0.945842;0.104576;-0.307323;,
  -0.989069;0.104578;0.103955;,
  -0.861276;0.104577;0.497260;,
  -0.584564;0.104579;0.804579;,
  -0.206774;0.104580;0.972783;,
  0.206774;0.104580;0.972783;,
  0.584564;0.104579;0.804579;,
  0.861276;0.104578;0.497259;,
  0.989069;0.104579;0.103955;,
  0.945842;0.104576;-0.307323;,
  0.739071;0.104576;-0.665461;,
  0.404504;0.104577;-0.908537;,
  0.000000;-0.104576;-0.994517;,
  -0.404504;-0.104577;-0.908537;,
  -0.739071;-0.104576;-0.665461;,
  -0.945842;-0.104577;-0.307323;,
  -0.989069;-0.104578;0.103956;,
  -0.861276;-0.104578;0.497260;,
  -0.584564;-0.104580;0.804579;,
  -0.206774;-0.104580;0.972783;,
  0.206774;-0.104580;0.972783;,
  0.584564;-0.104580;0.804579;,
  0.861276;-0.104579;0.497259;,
  0.989069;-0.104579;0.103955;,
  0.945842;-0.104577;-0.307323;,
  0.739071;-0.104576;-0.665461;,
  0.404504;-0.104577;-0.908537;,
  0.000000;-0.309145;-0.951015;,
  -0.386811;-0.309148;-0.868795;,
  -0.706741;-0.309150;-0.636352;,
  -0.904468;-0.309151;-0.293878;,
  -0.945804;-0.309149;0.099409;,
  -0.823601;-0.309148;0.475508;,
  -0.558991;-0.309149;0.769387;,
  -0.197728;-0.309153;0.930230;,
  0.197728;-0.309153;0.930230;,
  0.558991;-0.309149;0.769387;,
  0.823602;-0.309148;0.475508;,
  0.945804;-0.309149;0.099408;,
  0.904468;-0.309151;-0.293878;,
  0.706741;-0.309150;-0.636352;,
  0.386811;-0.309148;-0.868795;,
  0.000000;-0.500179;-0.865922;,
  -0.352202;-0.500180;-0.791058;,
  -0.643505;-0.500180;-0.579415;,
  -0.823542;-0.500178;-0.267584;,
  -0.861179;-0.500177;0.090516;,
  -0.749909;-0.500181;0.432962;,
  -0.508975;-0.500180;0.700546;,
  -0.180036;-0.500180;0.846999;,
  0.180036;-0.500180;0.846999;,
  0.508975;-0.500180;0.700546;,
  0.749909;-0.500180;0.432962;,
  0.861180;-0.500177;0.090515;,
  0.823541;-0.500178;-0.267584;,
  0.643505;-0.500180;-0.579415;,
  0.352202;-0.500180;-0.791058;,
  0.000000;-0.669311;-0.742982;,
  -0.302199;-0.669311;-0.678748;,
  -0.552144;-0.669311;-0.497152;,
  -0.706618;-0.669311;-0.229594;,
  -0.738911;-0.669312;0.077666;,
  -0.643441;-0.669311;0.371492;,
  -0.436714;-0.669311;0.601085;,
  -0.154475;-0.669311;0.726746;,
  0.154475;-0.669311;0.726746;,
  0.436714;-0.669311;0.601085;,
  0.643441;-0.669311;0.371492;,
  0.738911;-0.669312;0.077666;,
  0.706618;-0.669311;-0.229594;,
  0.552144;-0.669311;-0.497152;,
  0.302199;-0.669311;-0.678748;,
  0.000000;-0.809153;-0.587599;,
  -0.238998;-0.809152;-0.536799;,
  -0.436671;-0.809152;-0.393180;,
  -0.558839;-0.809153;-0.181578;,
  -0.584380;-0.809152;0.061422;,
  -0.508878;-0.809150;0.293803;,
  -0.345383;-0.809151;0.475379;,
  -0.122169;-0.809151;0.574760;,
  0.122169;-0.809151;0.574760;,
  0.345383;-0.809151;0.475379;,
  0.508878;-0.809150;0.293803;,
  0.584380;-0.809152;0.061422;,
  0.558839;-0.809153;-0.181578;,
  0.436671;-0.809152;-0.393180;,
  0.238998;-0.809152;-0.536799;,
  0.000000;-0.913616;-0.406577;,
  -0.165369;-0.913616;-0.371428;,
  -0.302147;-0.913615;-0.272055;,
  -0.386682;-0.913614;-0.125642;,
  -0.404354;-0.913615;0.042500;,
  -0.352108;-0.913615;0.203293;,
  -0.238982;-0.913615;0.328930;,
  -0.084534;-0.913615;0.397696;,
  0.084534;-0.913615;0.397696;,
  0.238982;-0.913615;0.328930;,
  0.352108;-0.913615;0.203293;,
  0.404354;-0.913615;0.042500;,
  0.386682;-0.913614;-0.125642;,
  0.302147;-0.913615;-0.272055;,
  0.165369;-0.913616;-0.371428;,
  0.000000;-0.978168;-0.207814;,
  -0.084524;-0.978168;-0.189849;,
  -0.154434;-0.978169;-0.139056;,
  -0.197642;-0.978168;-0.064219;,
  -0.206674;-0.978169;0.021724;,
  -0.179971;-0.978168;0.103910;,
  -0.122151;-0.978168;0.168124;,
  -0.043208;-0.978168;0.203272;,
  0.043208;-0.978168;0.203272;,
  0.122151;-0.978168;0.168124;,
  0.179971;-0.978168;0.103910;,
  0.206674;-0.978169;0.021724;,
  0.197642;-0.978168;-0.064219;,
  0.154434;-0.978169;-0.139056;,
  0.084524;-0.978168;-0.189849;,
  0.000000;-1.000000;-0.000000;;
  225;
  3;1,2,0;,
  3;2,3,0;,
  3;3,4,0;,
  3;4,5,0;,
  3;5,6,0;,
  3;6,7,0;,
  3;7,8,0;,
  3;8,9,0;,
  3;9,10,0;,
  3;10,11,0;,
  3;11,12,0;,
  3;12,13,0;,
  3;13,14,0;,
  3;14,15,0;,
  3;15,1,0;,
  4;16,17,2,1;,
  4;17,18,3,2;,
  4;18,19,4,3;,
  4;19,20,5,4;,
  4;20,21,6,5;,
  4;21,22,7,6;,
  4;22,23,8,7;,
  4;23,24,9,8;,
  4;24,25,10,9;,
  4;25,26,11,10;,
  4;26,27,12,11;,
  4;27,28,13,12;,
  4;28,29,14,13;,
  4;29,30,15,14;,
  4;30,16,1,15;,
  4;31,32,17,16;,
  4;32,33,18,17;,
  4;33,34,19,18;,
  4;34,35,20,19;,
  4;35,36,21,20;,
  4;36,37,22,21;,
  4;37,38,23,22;,
  4;38,39,24,23;,
  4;39,40,25,24;,
  4;40,41,26,25;,
  4;41,42,27,26;,
  4;42,43,28,27;,
  4;43,44,29,28;,
  4;44,45,30,29;,
  4;45,31,16,30;,
  4;46,47,32,31;,
  4;47,48,33,32;,
  4;48,49,34,33;,
  4;49,50,35,34;,
  4;50,51,36,35;,
  4;51,52,37,36;,
  4;52,53,38,37;,
  4;53,54,39,38;,
  4;54,55,40,39;,
  4;55,56,41,40;,
  4;56,57,42,41;,
  4;57,58,43,42;,
  4;58,59,44,43;,
  4;59,60,45,44;,
  4;60,46,31,45;,
  4;61,62,47,46;,
  4;62,63,48,47;,
  4;63,64,49,48;,
  4;64,65,50,49;,
  4;65,66,51,50;,
  4;66,67,52,51;,
  4;67,68,53,52;,
  4;68,69,54,53;,
  4;69,70,55,54;,
  4;70,71,56,55;,
  4;71,72,57,56;,
  4;72,73,58,57;,
  4;73,74,59,58;,
  4;74,75,60,59;,
  4;75,61,46,60;,
  4;76,77,62,61;,
  4;77,78,63,62;,
  4;78,79,64,63;,
  4;79,80,65,64;,
  4;80,81,66,65;,
  4;81,82,67,66;,
  4;82,83,68,67;,
  4;83,84,69,68;,
  4;84,85,70,69;,
  4;85,86,71,70;,
  4;86,87,72,71;,
  4;87,88,73,72;,
  4;88,89,74,73;,
  4;89,90,75,74;,
  4;90,76,61,75;,
  4;91,92,77,76;,
  4;92,93,78,77;,
  4;93,94,79,78;,
  4;94,95,80,79;,
  4;95,96,81,80;,
  4;96,97,82,81;,
  4;97,98,83,82;,
  4;98,99,84,83;,
  4;99,100,85,84;,
  4;100,101,86,85;,
  4;101,102,87,86;,
  4;102,103,88,87;,
  4;103,104,89,88;,
  4;104,105,90,89;,
  4;105,91,76,90;,
  4;106,107,92,91;,
  4;107,108,93,92;,
  4;108,109,94,93;,
  4;109,110,95,94;,
  4;110,111,96,95;,
  4;111,112,97,96;,
  4;112,113,98,97;,
  4;113,114,99,98;,
  4;114,115,100,99;,
  4;115,116,101,100;,
  4;116,117,102,101;,
  4;117,118,103,102;,
  4;118,119,104,103;,
  4;119,120,105,104;,
  4;120,106,91,105;,
  4;121,122,107,106;,
  4;122,123,108,107;,
  4;123,124,109,108;,
  4;124,125,110,109;,
  4;125,126,111,110;,
  4;126,127,112,111;,
  4;127,128,113,112;,
  4;128,129,114,113;,
  4;129,130,115,114;,
  4;130,131,116,115;,
  4;131,132,117,116;,
  4;132,133,118,117;,
  4;133,134,119,118;,
  4;134,135,120,119;,
  4;135,121,106,120;,
  4;136,137,122,121;,
  4;137,138,123,122;,
  4;138,139,124,123;,
  4;139,140,125,124;,
  4;140,141,126,125;,
  4;141,142,127,126;,
  4;142,143,128,127;,
  4;143,144,129,128;,
  4;144,145,130,129;,
  4;145,146,131,130;,
  4;146,147,132,131;,
  4;147,148,133,132;,
  4;148,149,134,133;,
  4;149,150,135,134;,
  4;150,136,121,135;,
  4;151,152,137,136;,
  4;152,153,138,137;,
  4;153,154,139,138;,
  4;154,155,140,139;,
  4;155,156,141,140;,
  4;156,157,142,141;,
  4;157,158,143,142;,
  4;158,159,144,143;,
  4;159,160,145,144;,
  4;160,161,146,145;,
  4;161,162,147,146;,
  4;162,163,148,147;,
  4;163,164,149,148;,
  4;164,165,150,149;,
  4;165,151,136,150;,
  4;166,167,152,151;,
  4;167,168,153,152;,
  4;168,169,154,153;,
  4;169,170,155,154;,
  4;170,171,156,155;,
  4;171,172,157,156;,
  4;172,173,158,157;,
  4;173,174,159,158;,
  4;174,175,160,159;,
  4;175,176,161,160;,
  4;176,177,162,161;,
  4;177,178,163,162;,
  4;178,179,164,163;,
  4;179,180,165,164;,
  4;180,166,151,165;,
  4;181,182,167,166;,
  4;182,183,168,167;,
  4;183,184,169,168;,
  4;184,185,170,169;,
  4;185,186,171,170;,
  4;186,187,172,171;,
  4;187,188,173,172;,
  4;188,189,174,173;,
  4;189,190,175,174;,
  4;190,191,176,175;,
  4;191,192,177,176;,
  4;192,193,178,177;,
  4;193,194,179,178;,
  4;194,195,180,179;,
  4;195,181,166,180;,
  4;196,197,182,181;,
  4;197,198,183,182;,
  4;198,199,184,183;,
  4;199,200,185,184;,
  4;200,201,186,185;,
  4;201,202,187,186;,
  4;202,203,188,187;,
  4;203,204,189,188;,
  4;204,205,190,189;,
  4;205,206,191,190;,
  4;206,207,192,191;,
  4;207,208,193,192;,
  4;208,209,194,193;,
  4;209,210,195,194;,
  4;210,196,181,195;,
  3;211,197,196;,
  3;211,198,197;,
  3;211,199,198;,
  3;211,200,199;,
  3;211,201,200;,
  3;211,202,201;,
  3;211,203,202;,
  3;211,204,203;,
  3;211,205,204;,
  3;211,206,205;,
  3;211,207,206;,
  3;211,208,207;,
  3;211,209,208;,
  3;211,210,209;,
  3;211,196,210;;
 }
 MeshTextureCoords {
  254;
  0.033330;0.000000;,
  0.066670;0.066670;,
  0.000000;0.066670;,
  0.100000;0.000000;,
  0.133330;0.066670;,
  0.166670;0.000000;,
  0.200000;0.066670;,
  0.233330;0.000000;,
  0.266670;0.066670;,
  0.300000;0.000000;,
  0.333330;0.066670;,
  0.366670;0.000000;,
  0.400000;0.066670;,
  0.433330;0.000000;,
  0.466670;0.066670;,
  0.500000;0.000000;,
  0.533330;0.066670;,
  0.566670;0.000000;,
  0.600000;0.066670;,
  0.633330;0.000000;,
  0.666670;0.066670;,
  0.700000;0.000000;,
  0.733330;0.066670;,
  0.766670;0.000000;,
  0.800000;0.066670;,
  0.833330;0.000000;,
  0.866670;0.066670;,
  0.900000;0.000000;,
  0.933330;0.066670;,
  0.966670;0.000000;,
  1.000000;0.066670;,
  0.066670;0.133330;,
  0.000000;0.133330;,
  0.133330;0.133330;,
  0.200000;0.133330;,
  0.266670;0.133330;,
  0.333330;0.133330;,
  0.400000;0.133330;,
  0.466670;0.133330;,
  0.533330;0.133330;,
  0.600000;0.133330;,
  0.666670;0.133330;,
  0.733330;0.133330;,
  0.800000;0.133330;,
  0.866670;0.133330;,
  0.933330;0.133330;,
  1.000000;0.133330;,
  0.066670;0.200000;,
  0.000000;0.200000;,
  0.133330;0.200000;,
  0.200000;0.200000;,
  0.266670;0.200000;,
  0.333330;0.200000;,
  0.400000;0.200000;,
  0.466670;0.200000;,
  0.533330;0.200000;,
  0.600000;0.200000;,
  0.666670;0.200000;,
  0.733330;0.200000;,
  0.800000;0.200000;,
  0.866670;0.200000;,
  0.933330;0.200000;,
  1.000000;0.200000;,
  0.066670;0.266670;,
  0.000000;0.266670;,
  0.133330;0.266670;,
  0.200000;0.266670;,
  0.266670;0.266670;,
  0.333330;0.266670;,
  0.400000;0.266670;,
  0.466670;0.266670;,
  0.533330;0.266670;,
  0.600000;0.266670;,
  0.666670;0.266670;,
  0.733330;0.266670;,
  0.800000;0.266670;,
  0.866670;0.266670;,
  0.933330;0.266670;,
  1.000000;0.266670;,
  0.066670;0.333330;,
  0.000000;0.333330;,
  0.133330;0.333330;,
  0.200000;0.333330;,
  0.266670;0.333330;,
  0.333330;0.333330;,
  0.400000;0.333330;,
  0.466670;0.333330;,
  0.533330;0.333330;,
  0.600000;0.333330;,
  0.666670;0.333330;,
  0.733330;0.333330;,
  0.800000;0.333330;,
  0.866670;0.333330;,
  0.933330;0.333330;,
  1.000000;0.333330;,
  0.066670;0.400000;,
  0.000000;0.400000;,
  0.133330;0.400000;,
  0.200000;0.400000;,
  0.266670;0.400000;,
  0.333330;0.400000;,
  0.400000;0.400000;,
  0.466670;0.400000;,
  0.533330;0.400000;,
  0.600000;0.400000;,
  0.666670;0.400000;,
  0.733330;0.400000;,
  0.800000;0.400000;,
  0.866670;0.400000;,
  0.933330;0.400000;,
  1.000000;0.400000;,
  0.066670;0.466670;,
  0.000000;0.466670;,
  0.133330;0.466670;,
  0.200000;0.466670;,
  0.266670;0.466670;,
  0.333330;0.466670;,
  0.400000;0.466670;,
  0.466670;0.466670;,
  0.533330;0.466670;,
  0.600000;0.466670;,
  0.666670;0.466670;,
  0.733330;0.466670;,
  0.800000;0.466670;,
  0.866670;0.466670;,
  0.933330;0.466670;,
  1.000000;0.466670;,
  0.066670;0.533330;,
  0.000000;0.533330;,
  0.133330;0.533330;,
  0.200000;0.533330;,
  0.266670;0.533330;,
  0.333330;0.533330;,
  0.400000;0.533330;,
  0.466670;0.533330;,
  0.533330;0.533330;,
  0.600000;0.533330;,
  0.666670;0.533330;,
  0.733330;0.533330;,
  0.800000;0.533330;,
  0.866670;0.533330;,
  0.933330;0.533330;,
  1.000000;0.533330;,
  0.066670;0.600000;,
  0.000000;0.600000;,
  0.133330;0.600000;,
  0.200000;0.600000;,
  0.266670;0.600000;,
  0.333330;0.600000;,
  0.400000;0.600000;,
  0.466670;0.600000;,
  0.533330;0.600000;,
  0.600000;0.600000;,
  0.666670;0.600000;,
  0.733330;0.600000;,
  0.800000;0.600000;,
  0.866670;0.600000;,
  0.933330;0.600000;,
  1.000000;0.600000;,
  0.066670;0.666670;,
  0.000000;0.666670;,
  0.133330;0.666670;,
  0.200000;0.666670;,
  0.266670;0.666670;,
  0.333330;0.666670;,
  0.400000;0.666670;,
  0.466670;0.666670;,
  0.533330;0.666670;,
  0.600000;0.666670;,
  0.666670;0.666670;,
  0.733330;0.666670;,
  0.800000;0.666670;,
  0.866670;0.666670;,
  0.933330;0.666670;,
  1.000000;0.666670;,
  0.066670;0.733330;,
  0.000000;0.733330;,
  0.133330;0.733330;,
  0.200000;0.733330;,
  0.266670;0.733330;,
  0.333330;0.733330;,
  0.400000;0.733330;,
  0.466670;0.733330;,
  0.533330;0.733330;,
  0.600000;0.733330;,
  0.666670;0.733330;,
  0.733330;0.733330;,
  0.800000;0.733330;,
  0.866670;0.733330;,
  0.933330;0.733330;,
  1.000000;0.733330;,
  0.066670;0.800000;,
  0.000000;0.800000;,
  0.133330;0.800000;,
  0.200000;0.800000;,
  0.266670;0.800000;,
  0.333330;0.800000;,
  0.400000;0.800000;,
  0.466670;0.800000;,
  0.533330;0.800000;,
  0.600000;0.800000;,
  0.666670;0.800000;,
  0.733330;0.800000;,
  0.800000;0.800000;,
  0.866670;0.800000;,
  0.933330;0.800000;,
  1.000000;0.800000;,
  0.066670;0.866670;,
  0.000000;0.866670;,
  0.133330;0.866670;,
  0.200000;0.866670;,
  0.266670;0.866670;,
  0.333330;0.866670;,
  0.400000;0.866670;,
  0.466670;0.866670;,
  0.533330;0.866670;,
  0.600000;0.866670;,
  0.666670;0.866670;,
  0.733330;0.866670;,
  0.800000;0.866670;,
  0.866670;0.866670;,
  0.933330;0.866670;,
  1.000000;0.866670;,
  0.066670;0.933330;,
  0.000000;0.933330;,
  0.133330;0.933330;,
  0.200000;0.933330;,
  0.266670;0.933330;,
  0.333330;0.933330;,
  0.400000;0.933330;,
  0.466670;0.933330;,
  0.533330;0.933330;,
  0.600000;0.933330;,
  0.666670;0.933330;,
  0.733330;0.933330;,
  0.800000;0.933330;,
  0.866670;0.933330;,
  0.933330;0.933330;,
  1.000000;0.933330;,
  0.033330;1.000000;,
  0.100000;1.000000;,
  0.166670;1.000000;,
  0.233330;1.000000;,
  0.300000;1.000000;,
  0.366670;1.000000;,
  0.433330;1.000000;,
  0.500000;1.000000;,
  0.566670;1.000000;,
  0.633330;1.000000;,
  0.700000;1.000000;,
  0.766670;1.000000;,
  0.833330;1.000000;,
  0.900000;1.000000;,
  0.966670;1.000000;;
 }
}