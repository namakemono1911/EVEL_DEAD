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
 120;
 4.99853;19.86595;-0.83426;,
 4.44988;19.86595;-0.83426;,
 4.44988;-0.03453;-0.83426;,
 4.99853;-0.03453;-0.83426;,
 4.44988;19.86595;-0.83426;,
 4.44988;19.86595;0.83426;,
 4.44988;-0.03453;0.83426;,
 4.44988;-0.03453;-0.83426;,
 4.44988;19.86595;0.83426;,
 4.99853;19.86595;0.83426;,
 4.99853;-0.03453;0.83426;,
 4.44988;-0.03453;0.83426;,
 4.99853;19.86595;0.83426;,
 4.99853;19.86595;-0.83426;,
 4.99853;-0.03453;-0.83426;,
 4.99853;-0.03453;0.83426;,
 4.44988;19.86595;-0.83426;,
 4.99853;19.86595;-0.83426;,
 4.99853;-0.03453;-0.83426;,
 4.44988;-0.03453;-0.83426;,
 -4.99853;-0.03453;-0.83426;,
 -4.44988;-0.03453;-0.83426;,
 -4.44988;19.86595;-0.83426;,
 -4.99853;19.86595;-0.83426;,
 -4.44988;-0.03453;-0.83426;,
 -4.44988;-0.03453;0.83426;,
 -4.44988;19.86595;0.83426;,
 -4.44988;19.86595;-0.83426;,
 -4.44988;-0.03453;0.83426;,
 -4.99853;-0.03453;0.83426;,
 -4.99853;19.86595;0.83426;,
 -4.44988;19.86595;0.83426;,
 -4.99853;-0.03453;0.83426;,
 -4.99853;-0.03453;-0.83426;,
 -4.99853;19.86595;-0.83426;,
 -4.99853;19.86595;0.83426;,
 -4.99853;19.86595;-0.83426;,
 -4.44988;19.86595;-0.83426;,
 -4.44988;-0.03453;-0.83426;,
 -4.99853;-0.03453;-0.83426;,
 5.00742;20.46482;-0.83426;,
 -4.99138;20.46482;-0.83426;,
 -4.99138;19.81477;-0.83426;,
 5.00742;19.81477;-0.83426;,
 -4.99138;20.46482;-0.83426;,
 -4.99138;20.46482;0.83426;,
 -4.99138;19.81477;0.83426;,
 -4.99138;19.81477;-0.83426;,
 -4.99138;20.46482;0.83426;,
 5.00742;20.46482;0.83426;,
 5.00742;19.81477;0.83426;,
 -4.99138;19.81477;0.83426;,
 5.00742;20.46482;0.83426;,
 5.00742;20.46482;-0.83426;,
 5.00742;19.81477;-0.83426;,
 5.00742;19.81477;0.83426;,
 -4.99138;20.46482;-0.83426;,
 5.00742;20.46482;-0.83426;,
 5.00742;19.81477;-0.83426;,
 -4.99138;19.81477;-0.83426;,
 -14.90338;7.36123;0.72191;,
 -14.90338;0.01199;0.72191;,
 -14.90338;0.01199;-0.72191;,
 -14.90338;7.36123;-0.72191;,
 14.90338;7.36123;-0.72191;,
 14.90338;0.01199;-0.72191;,
 14.90338;0.01199;0.72191;,
 14.90338;7.36123;0.72191;,
 4.70268;21.35975;0.72191;,
 4.70268;21.35975;-0.72191;,
 14.90338;21.35975;-0.72191;,
 14.90338;21.35975;0.72191;,
 4.70268;0.01199;-0.72191;,
 4.70268;0.01199;0.72191;,
 14.90338;0.01199;-0.72191;,
 4.70268;0.01199;-0.72191;,
 14.90338;0.01199;-0.72191;,
 14.90338;7.36123;-0.72191;,
 4.70268;7.36123;-0.72191;,
 4.70268;0.01199;0.72191;,
 4.70268;7.36123;0.72191;,
 14.90338;7.36123;0.72191;,
 14.90338;0.01199;0.72191;,
 -4.69960;21.35975;0.72191;,
 -14.90338;21.35975;0.72191;,
 -14.90338;21.35975;-0.72191;,
 -4.69960;21.35975;-0.72191;,
 -4.69960;0.01199;-0.72191;,
 -14.90338;0.01199;-0.72191;,
 -4.69960;0.01199;0.72191;,
 -4.69960;7.36123;-0.72191;,
 -14.90338;7.36123;-0.72191;,
 -14.90338;0.01199;-0.72191;,
 -4.69960;0.01199;-0.72191;,
 -4.69960;0.01199;0.72191;,
 -14.90338;0.01199;0.72191;,
 -14.90338;7.36123;0.72191;,
 -4.69960;7.36123;0.72191;,
 -14.90338;20.24675;-0.72191;,
 -14.90338;21.35975;-0.72191;,
 -14.90338;20.24675;0.72191;,
 14.90338;20.24675;0.72191;,
 14.90338;21.35975;-0.72191;,
 14.90338;20.24675;-0.72191;,
 14.90338;20.24675;-0.72191;,
 14.90338;21.35975;-0.72191;,
 4.70268;21.35975;-0.72191;,
 4.70268;20.24675;-0.72191;,
 4.70268;20.24675;0.72191;,
 4.70268;21.35975;0.72191;,
 14.90338;21.35975;0.72191;,
 14.90338;20.24675;0.72191;,
 -14.90338;20.24675;-0.72191;,
 -4.69960;20.24675;-0.72191;,
 -4.69960;21.35975;-0.72191;,
 -14.90338;21.35975;-0.72191;,
 -14.90338;20.24675;0.72191;,
 -14.90338;21.35975;0.72191;,
 -4.69960;21.35975;0.72191;,
 -4.69960;20.24675;0.72191;;
 
 43;
 4;3,2,1,0;,
 4;7,6,5,4;,
 4;11,10,9,8;,
 4;15,14,13,12;,
 4;17,16,5,12;,
 4;15,6,19,18;,
 4;23,22,21,20;,
 4;27,26,25,24;,
 4;31,30,29,28;,
 4;35,34,33,32;,
 4;35,26,37,36;,
 4;39,38,25,32;,
 4;43,42,41,40;,
 4;47,46,45,44;,
 4;51,50,49,48;,
 4;55,54,53,52;,
 4;57,56,45,52;,
 4;55,46,59,58;,
 4;63,62,61,60;,
 4;67,66,65,64;,
 4;71,70,69,68;,
 4;74,66,73,72;,
 4;78,77,76,75;,
 4;82,81,80,79;,
 4;86,85,84,83;,
 4;68,69,86,83;,
 4;89,61,88,87;,
 4;93,92,91,90;,
 4;97,96,95,94;,
 4;100,84,99,98;,
 4;63,60,100,98;,
 4;103,102,71,101;,
 4;67,64,103,101;,
 4;107,106,105,104;,
 4;77,78,107,104;,
 4;111,110,109,108;,
 4;80,81,111,108;,
 4;113,90,91,112;,
 4;115,114,113,112;,
 4;114,106,107,113;,
 4;119,118,117,116;,
 4;96,97,119,116;,
 4;108,109,118,119;;
 
 MeshMaterialList {
  3;
  43;
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
  1,
  1,
  0,
  0,
  0,
  2,
  0,
  0,
  0,
  0,
  2,
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
   0.800000;0.800000;0.800000;1.000000;;
   5.000000;
   0.000000;0.000000;0.000000;;
   0.000000;0.000000;0.000000;;
   TextureFilename {
    "data\\texture\\depositphotos_11955619-stock-photo-background-of-stone-wall-texture.jpg";
   }
  }
  Material {
   0.800000;0.800000;0.800000;1.000000;;
   5.000000;
   0.000000;0.000000;0.000000;;
   0.000000;0.000000;0.000000;;
   TextureFilename {
    "data\\texture\\Wood_Dark-Mahony.jpg";
   }
  }
  Material {
   1.000000;1.000000;1.000000;1.000000;;
   0.000000;
   0.000000;0.000000;0.000000;;
   0.000000;0.000000;0.000000;;
  }
 }
 MeshNormals {
  24;
  0.000000;0.000000;-1.000000;,
  -1.000000;0.000000;0.000000;,
  0.000000;0.000000;1.000000;,
  1.000000;0.000000;0.000000;,
  0.000000;1.000000;0.000000;,
  0.000000;-1.000000;0.000000;,
  0.000000;0.000000;-1.000000;,
  -1.000000;0.000000;0.000000;,
  0.000000;0.000000;1.000000;,
  1.000000;0.000000;0.000000;,
  0.000000;1.000000;0.000000;,
  0.000000;-1.000000;0.000000;,
  0.000000;1.000000;0.000000;,
  1.000000;0.000000;0.000000;,
  -1.000000;0.000000;0.000000;,
  0.000000;-1.000000;0.000000;,
  0.000000;0.000000;-1.000000;,
  0.000000;0.000000;1.000000;,
  -0.000000;0.000000;-1.000000;,
  0.000000;0.000000;-1.000000;,
  -0.000000;0.000000;-1.000000;,
  0.000000;0.000000;-1.000000;,
  0.000000;0.000000;-1.000000;,
  -0.000000;0.000000;-1.000000;;
  43;
  4;0,0,0,0;,
  4;1,1,1,1;,
  4;2,2,2,2;,
  4;3,3,3,3;,
  4;4,4,4,4;,
  4;5,5,5,5;,
  4;0,0,0,0;,
  4;3,3,3,3;,
  4;2,2,2,2;,
  4;1,1,1,1;,
  4;4,4,4,4;,
  4;5,5,5,5;,
  4;6,6,6,6;,
  4;7,7,7,7;,
  4;8,8,8,8;,
  4;9,9,9,9;,
  4;10,10,10,10;,
  4;11,11,11,11;,
  4;14,14,14,14;,
  4;13,13,13,13;,
  4;12,12,12,12;,
  4;15,15,15,15;,
  4;16,16,16,16;,
  4;17,17,17,17;,
  4;12,12,12,12;,
  4;12,12,12,12;,
  4;15,15,15,15;,
  4;18,18,18,18;,
  4;17,17,17,17;,
  4;14,14,14,14;,
  4;14,14,14,14;,
  4;13,13,13,13;,
  4;13,13,13,13;,
  4;19,22,21,16;,
  4;16,16,19,16;,
  4;17,17,17,17;,
  4;17,17,17,17;,
  4;20,18,18,18;,
  4;18,23,20,18;,
  4;23,22,19,20;,
  4;17,17,17,17;,
  4;17,17,17,17;,
  4;17,17,17,17;;
 }
 MeshTextureCoords {
  120;
  0.000000;0.000000;,
  1.000000;0.000000;,
  1.000000;1.000000;,
  0.000000;1.000000;,
  0.000000;0.000000;,
  1.000000;0.000000;,
  1.000000;1.000000;,
  0.000000;1.000000;,
  0.000000;0.000000;,
  1.000000;0.000000;,
  1.000000;1.000000;,
  0.000000;1.000000;,
  0.000000;0.000000;,
  1.000000;0.000000;,
  1.000000;1.000000;,
  0.000000;1.000000;,
  1.000000;1.000000;,
  0.000000;1.000000;,
  0.000000;0.000000;,
  1.000000;0.000000;,
  0.000000;1.000000;,
  1.000000;1.000000;,
  1.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;1.000000;,
  1.000000;1.000000;,
  1.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;1.000000;,
  1.000000;1.000000;,
  1.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;1.000000;,
  1.000000;1.000000;,
  1.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;1.000000;,
  1.000000;1.000000;,
  1.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  1.000000;0.000000;,
  1.000000;1.000000;,
  0.000000;1.000000;,
  0.000000;0.000000;,
  1.000000;0.000000;,
  1.000000;1.000000;,
  0.000000;1.000000;,
  0.000000;0.000000;,
  1.000000;0.000000;,
  1.000000;1.000000;,
  0.000000;1.000000;,
  0.000000;0.000000;,
  1.000000;0.000000;,
  1.000000;1.000000;,
  0.000000;1.000000;,
  1.000000;1.000000;,
  0.000000;1.000000;,
  0.000000;0.000000;,
  1.000000;0.000000;,
  1.000000;0.655737;,
  1.000000;1.000000;,
  0.000000;1.000000;,
  0.000000;0.655737;,
  1.000000;0.655737;,
  1.000000;1.000000;,
  0.000000;1.000000;,
  0.000000;0.655737;,
  0.342228;0.000000;,
  0.342228;1.000000;,
  0.000000;1.000000;,
  0.000000;0.000000;,
  0.342228;0.000000;,
  0.342228;1.000000;,
  0.000000;0.000000;,
  0.342228;1.000000;,
  0.000000;1.000000;,
  0.000000;0.655737;,
  0.342228;0.655737;,
  0.657772;1.000000;,
  0.657772;0.655737;,
  1.000000;0.655737;,
  1.000000;1.000000;,
  0.657669;0.000000;,
  1.000000;0.000000;,
  1.000000;1.000000;,
  0.657669;1.000000;,
  0.657669;0.000000;,
  1.000000;0.000000;,
  0.657669;1.000000;,
  0.657669;0.655737;,
  1.000000;0.655737;,
  1.000000;1.000000;,
  0.657669;1.000000;,
  0.342331;1.000000;,
  0.000000;1.000000;,
  0.000000;0.655737;,
  0.342331;0.655737;,
  0.000000;0.052137;,
  0.000000;0.000000;,
  1.000000;0.052137;,
  0.000000;0.052137;,
  1.000000;0.000000;,
  1.000000;0.052137;,
  0.000000;0.052137;,
  0.000000;0.000000;,
  0.342228;0.000000;,
  0.342228;0.052137;,
  0.657772;0.052137;,
  0.657772;0.000000;,
  1.000000;0.000000;,
  1.000000;0.052137;,
  1.000000;0.052137;,
  0.657669;0.052137;,
  0.657669;0.000000;,
  1.000000;0.000000;,
  0.000000;0.052137;,
  0.000000;0.000000;,
  0.342331;0.000000;,
  0.342331;0.052137;;
 }
}
