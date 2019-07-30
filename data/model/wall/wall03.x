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
 69;
 149.28108;214.33013;7.19513;,
 -149.28108;214.33013;7.19513;,
 -149.28108;214.33013;-7.19513;,
 149.28108;214.33013;-7.19513;,
 -149.28108;74.56542;7.19513;,
 -149.28108;0.57826;7.19513;,
 -149.28108;0.57826;-7.19513;,
 -149.28108;74.56542;-7.19513;,
 -149.28108;214.33013;-7.19513;,
 149.28108;74.56542;-7.19513;,
 149.28108;0.57826;-7.19513;,
 149.28108;0.57826;7.19513;,
 149.28108;74.56542;7.19513;,
 149.28108;214.33013;-7.19513;,
 -111.96082;0.57826;7.19513;,
 -149.28108;0.57826;7.19513;,
 -149.28108;74.56542;7.19513;,
 -111.96082;74.56542;7.19513;,
 -74.64054;74.56542;7.19513;,
 -74.64054;0.57826;7.19513;,
 -37.32027;0.57826;7.19513;,
 -37.32027;74.56542;7.19513;,
 0.00000;74.56542;7.19513;,
 0.00000;0.57826;7.19513;,
 37.32027;0.57826;7.19513;,
 37.32027;74.56542;7.19513;,
 74.64054;74.56542;7.19513;,
 74.64054;0.57826;7.19513;,
 111.96082;0.57826;7.19513;,
 111.96082;74.56542;7.19513;,
 149.28108;74.56542;7.19513;,
 149.28108;0.57826;7.19513;,
 111.96082;0.57826;-7.19513;,
 149.28108;0.57826;-7.19513;,
 149.28108;74.56542;-7.19513;,
 111.96082;74.56542;-7.19513;,
 74.64054;74.56542;-7.19513;,
 74.64054;0.57826;-7.19513;,
 37.32027;0.57826;-7.19513;,
 37.32027;74.56542;-7.19513;,
 0.00000;74.56542;-7.19513;,
 0.00000;0.57826;-7.19513;,
 -37.32027;0.57826;-7.19513;,
 -37.32027;74.56542;-7.19513;,
 -74.64054;74.56542;-7.19513;,
 -74.64054;0.57826;-7.19513;,
 -111.96082;0.57826;-7.19513;,
 -111.96082;74.56542;-7.19513;,
 -149.28108;74.56542;-7.19513;,
 -149.28108;0.57826;-7.19513;,
 -149.28108;214.33013;7.19513;,
 149.28108;214.33013;7.19513;,
 -111.96082;0.57826;7.19513;,
 -149.28108;0.57826;-7.19513;,
 -74.64054;0.57826;7.19513;,
 -37.32027;0.57826;7.19513;,
 37.32027;0.57826;7.19513;,
 74.64054;0.57826;7.19513;,
 111.96082;0.57826;7.19513;,
 149.28108;0.57826;-7.19513;,
 111.96082;0.57826;-7.19513;,
 74.64054;0.57826;-7.19513;,
 37.32027;0.57826;-7.19513;,
 0.00000;0.57826;-7.19513;,
 -37.32027;0.57826;-7.19513;,
 -74.64054;0.57826;-7.19513;,
 -111.96082;0.57826;-7.19513;,
 149.28108;214.33013;-7.19513;,
 -149.28108;214.33013;-7.19513;;
 
 55;
 4;3,2,1,0;,
 4;7,6,5,4;,
 4;4,1,8,7;,
 4;12,11,10,9;,
 4;9,13,0,12;,
 4;17,16,15,14;,
 4;14,19,18,17;,
 4;21,18,19,20;,
 4;20,23,22,21;,
 4;25,22,23,24;,
 4;24,27,26,25;,
 4;29,26,27,28;,
 4;28,31,30,29;,
 4;35,34,33,32;,
 4;32,37,36,35;,
 4;39,36,37,38;,
 4;38,41,40,39;,
 4;43,40,41,42;,
 4;42,45,44,43;,
 4;47,44,45,46;,
 4;46,49,48,47;,
 3;17,50,16;,
 3;51,29,30;,
 3;51,26,29;,
 3;51,25,26;,
 3;51,22,25;,
 3;51,21,22;,
 3;51,18,21;,
 3;51,17,18;,
 3;51,50,17;,
 3;53,52,5;,
 3;53,54,52;,
 3;53,55,54;,
 3;53,23,55;,
 3;53,56,23;,
 3;53,57,56;,
 3;53,58,57;,
 3;53,11,58;,
 3;60,59,11;,
 3;61,60,11;,
 3;62,61,11;,
 3;63,62,11;,
 3;64,63,11;,
 3;65,64,11;,
 3;66,65,11;,
 3;11,53,66;,
 3;35,67,34;,
 3;68,47,48;,
 3;68,44,47;,
 3;68,43,44;,
 3;68,40,43;,
 3;68,39,40;,
 3;68,36,39;,
 3;68,35,36;,
 3;68,67,35;;
 
 MeshMaterialList {
  2;
  55;
  0,
  1,
  0,
  1,
  0,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
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
   0.800000;0.800000;0.800000;1.000000;;
   5.000000;
   0.000000;0.000000;0.000000;;
   0.000000;0.000000;0.000000;;
   TextureFilename {
    "data\\texture\\wallpaper2.jpg";
   }
  }
  Material {
   0.800000;0.800000;0.800000;1.000000;;
   5.000000;
   0.000000;0.000000;0.000000;;
   0.000000;0.000000;0.000000;;
   TextureFilename {
    "data\\texture\\gatag-00011582.jpg";
   }
  }
 }
 MeshNormals {
  6;
  0.000000;1.000000;0.000000;,
  1.000000;0.000000;0.000000;,
  -1.000000;0.000000;0.000000;,
  0.000000;0.000000;-1.000000;,
  0.000000;0.000000;1.000000;,
  -0.000000;-1.000000;0.000000;;
  55;
  4;0,0,0,0;,
  4;2,2,2,2;,
  4;2,2,2,2;,
  4;1,1,1,1;,
  4;1,1,1,1;,
  4;4,4,4,4;,
  4;4,4,4,4;,
  4;4,4,4,4;,
  4;4,4,4,4;,
  4;4,4,4,4;,
  4;4,4,4,4;,
  4;4,4,4,4;,
  4;4,4,4,4;,
  4;3,3,3,3;,
  4;3,3,3,3;,
  4;3,3,3,3;,
  4;3,3,3,3;,
  4;3,3,3,3;,
  4;3,3,3,3;,
  4;3,3,3,3;,
  4;3,3,3,3;,
  3;4,4,4;,
  3;4,4,4;,
  3;4,4,4;,
  3;4,4,4;,
  3;4,4,4;,
  3;4,4,4;,
  3;4,4,4;,
  3;4,4,4;,
  3;4,4,4;,
  3;5,5,5;,
  3;5,5,5;,
  3;5,5,5;,
  3;5,5,5;,
  3;5,5,5;,
  3;5,5,5;,
  3;5,5,5;,
  3;5,5,5;,
  3;5,5,5;,
  3;5,5,5;,
  3;5,5,5;,
  3;5,5,5;,
  3;5,5,5;,
  3;5,5,5;,
  3;5,5,5;,
  3;5,5,5;,
  3;3,3,3;,
  3;3,3,3;,
  3;3,3,3;,
  3;3,3,3;,
  3;3,3,3;,
  3;3,3,3;,
  3;3,3,3;,
  3;3,3,3;,
  3;3,3,3;;
 }
 MeshTextureCoords {
  69;
  0.000000;0.000000;,
  1.000000;0.000000;,
  1.000000;1.000000;,
  0.000000;1.000000;,
  1.000000;0.653864;,
  1.000000;1.000000;,
  0.000000;1.000000;,
  0.000000;0.653864;,
  0.000000;0.000000;,
  1.000000;0.653864;,
  1.000000;1.000000;,
  0.000000;1.000000;,
  0.000000;0.653864;,
  1.000000;0.000000;,
  0.125000;1.000000;,
  0.000000;1.000000;,
  0.000000;0.653864;,
  0.125000;0.653864;,
  0.250000;0.653864;,
  0.250000;1.000000;,
  0.375000;1.000000;,
  0.375000;0.653864;,
  0.500000;0.653864;,
  0.500000;1.000000;,
  0.625000;1.000000;,
  0.625000;0.653864;,
  0.750000;0.653864;,
  0.750000;1.000000;,
  0.875000;1.000000;,
  0.875000;0.653864;,
  1.000000;0.653864;,
  1.000000;1.000000;,
  0.125000;1.000000;,
  0.000000;1.000000;,
  0.000000;0.653864;,
  0.125000;0.653864;,
  0.250000;0.653864;,
  0.250000;1.000000;,
  0.375000;1.000000;,
  0.375000;0.653864;,
  0.500000;0.653864;,
  0.500000;1.000000;,
  0.625000;1.000000;,
  0.625000;0.653864;,
  0.750000;0.653864;,
  0.750000;1.000000;,
  0.875000;1.000000;,
  0.875000;0.653864;,
  1.000000;0.653864;,
  1.000000;1.000000;,
  0.000000;0.000000;,
  1.000000;0.000000;,
  0.875000;1.000000;,
  1.000000;0.000000;,
  0.750000;1.000000;,
  0.625000;1.000000;,
  0.375000;1.000000;,
  0.250000;1.000000;,
  0.125000;1.000000;,
  0.000000;0.000000;,
  0.125000;0.000000;,
  0.250000;0.000000;,
  0.375000;0.000000;,
  0.500000;0.000000;,
  0.625000;0.000000;,
  0.750000;0.000000;,
  0.875000;0.000000;,
  0.000000;0.000000;,
  1.000000;0.000000;;
 }
}
