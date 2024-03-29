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
 60;
 0.50160;-0.08741;0.70413;,
 0.50160;0.08756;0.70413;,
 0.50160;0.08756;-0.70413;,
 0.50160;-0.08741;-0.70413;,
 -0.47684;-0.08741;-0.70413;,
 0.50160;-0.08741;-0.70413;,
 0.50160;0.08756;-0.70413;,
 -0.47684;0.08756;-0.70413;,
 -0.47684;0.08756;0.70413;,
 0.50160;0.08756;0.70413;,
 0.50160;-0.08741;0.70413;,
 -0.47684;-0.08741;0.70413;,
 -0.51159;0.08756;-0.71411;,
 -0.51159;0.11793;-0.71411;,
 -0.51159;0.11793;0.71411;,
 -0.51159;0.08756;0.71411;,
 0.51159;0.08756;0.71411;,
 0.51159;0.08756;-0.71411;,
 0.51159;0.11793;0.71411;,
 0.51159;0.11793;-0.71411;,
 -0.51159;-0.08741;0.71411;,
 -0.51159;-0.11793;0.71411;,
 -0.51159;-0.11793;-0.71411;,
 -0.51159;-0.08741;-0.71411;,
 0.51159;-0.08741;-0.71411;,
 0.51159;-0.08741;0.71411;,
 0.51159;-0.11793;-0.71411;,
 0.51159;-0.11793;0.71411;,
 -0.47684;0.11793;0.71411;,
 -0.51159;0.11793;-0.71411;,
 -0.47684;0.11793;-0.71411;,
 0.51159;0.11793;-0.71411;,
 -0.47684;-0.11793;-0.71411;,
 -0.51159;-0.11793;-0.71411;,
 -0.47684;-0.11793;0.71411;,
 0.51159;-0.11793;-0.71411;,
 -0.47684;0.11793;-0.71411;,
 -0.51159;0.11793;-0.71411;,
 -0.51159;0.08756;-0.71411;,
 -0.47684;0.08756;-0.71411;,
 0.51159;0.08756;-0.71411;,
 0.51159;0.11793;-0.71411;,
 -0.47684;0.08756;0.71411;,
 0.51159;0.08756;0.71411;,
 -0.47684;0.11793;0.71411;,
 0.51159;0.11793;0.71411;,
 -0.51159;0.08756;0.71411;,
 -0.51159;0.11793;0.71411;,
 -0.47684;-0.08741;-0.71411;,
 0.51159;-0.08741;-0.71411;,
 -0.47684;-0.11793;-0.71411;,
 0.51159;-0.11793;-0.71411;,
 -0.51159;-0.08741;-0.71411;,
 -0.51159;-0.11793;-0.71411;,
 -0.47684;-0.11793;0.71411;,
 -0.51159;-0.11793;0.71411;,
 -0.51159;-0.08741;0.71411;,
 -0.47684;-0.08741;0.71411;,
 0.51159;-0.08741;0.71411;,
 0.51159;-0.11793;0.71411;;
 
 30;
 4;3,2,1,0;,
 4;7,6,5,4;,
 4;11,10,9,8;,
 4;15,14,13,12;,
 4;1,2,17,16;,
 4;17,19,18,16;,
 4;23,22,21,20;,
 4;20,15,12,23;,
 4;3,0,25,24;,
 4;25,27,26,24;,
 4;30,29,14,28;,
 4;28,18,31,30;,
 4;34,21,33,32;,
 4;32,35,27,34;,
 4;39,38,37,36;,
 4;6,7,39,40;,
 4;36,41,40,39;,
 4;8,9,43,42;,
 4;42,43,45,44;,
 4;44,47,46,42;,
 4;4,5,49,48;,
 4;48,49,51,50;,
 4;50,53,52,48;,
 4;7,4,48,39;,
 4;48,52,38,39;,
 4;57,56,55,54;,
 4;10,11,57,58;,
 4;54,59,58,57;,
 4;11,8,42,57;,
 4;42,46,56,57;;
 
 MeshMaterialList {
  4;
  30;
  3,
  3,
  3,
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
    "data\\texture\\book07.jpg";
   }
  }
  Material {
   0.800000;0.800000;0.800000;1.000000;;
   5.000000;
   0.000000;0.000000;0.000000;;
   0.000000;0.000000;0.000000;;
   TextureFilename {
    "data\\texture\\book08.jpg";
   }
  }
  Material {
   0.800000;0.800000;0.800000;1.000000;;
   5.000000;
   0.000000;0.000000;0.000000;;
   0.000000;0.000000;0.000000;;
   TextureFilename {
    "data\\texture\\book07.jpg";
   }
  }
  Material {
   0.800000;0.800000;0.800000;1.000000;;
   5.000000;
   0.000000;0.000000;0.000000;;
   0.000000;0.000000;0.000000;;
   TextureFilename {
    "data\\texture\\paper.jpg";
   }
  }
 }
 MeshNormals {
  6;
  1.000000;0.000000;0.000000;,
  0.000000;0.000000;-1.000000;,
  0.000000;0.000000;1.000000;,
  -1.000000;0.000000;0.000000;,
  0.000000;-1.000000;0.000000;,
  0.000000;1.000000;0.000000;;
  30;
  4;0,0,0,0;,
  4;1,1,1,1;,
  4;2,2,2,2;,
  4;3,3,3,3;,
  4;4,4,4,4;,
  4;0,0,0,0;,
  4;3,3,3,3;,
  4;3,3,3,3;,
  4;5,5,5,5;,
  4;0,0,0,0;,
  4;5,5,5,5;,
  4;5,5,5,5;,
  4;4,4,4,4;,
  4;4,4,4,4;,
  4;1,1,1,1;,
  4;4,4,4,4;,
  4;1,1,1,1;,
  4;4,4,4,4;,
  4;2,2,2,2;,
  4;2,2,2,2;,
  4;5,5,5,5;,
  4;1,1,1,1;,
  4;1,1,1,1;,
  4;0,0,0,0;,
  4;1,1,1,1;,
  4;2,2,2,2;,
  4;5,5,5,5;,
  4;2,2,2,2;,
  4;0,0,0,0;,
  4;2,2,2,2;;
 }
 MeshTextureCoords {
  60;
  0.000000;0.730067;,
  0.000000;0.239257;,
  1.000000;0.239257;,
  1.000000;0.730067;,
  0.975312;0.730067;,
  0.000000;0.730067;,
  0.000000;0.239257;,
  0.975312;0.239257;,
  0.024688;0.239257;,
  1.000000;0.239257;,
  1.000000;0.730067;,
  0.024688;0.730067;,
  0.000000;0.239257;,
  0.000000;0.000000;,
  1.000000;0.000000;,
  1.000000;0.239257;,
  0.000000;0.239257;,
  1.000000;0.239257;,
  0.000000;0.000000;,
  1.000000;0.000000;,
  1.000000;0.730067;,
  1.000000;1.000000;,
  0.000000;1.000000;,
  0.000000;0.730067;,
  1.000000;0.730067;,
  0.000000;0.730067;,
  1.000000;1.000000;,
  0.000000;1.000000;,
  0.975312;0.000000;,
  1.000000;1.000000;,
  0.975312;1.000000;,
  0.000000;1.000000;,
  0.975312;0.000000;,
  1.000000;0.000000;,
  0.975312;1.000000;,
  0.000000;0.000000;,
  0.975312;0.000000;,
  1.000000;0.000000;,
  1.000000;0.239257;,
  0.975312;0.239257;,
  0.000000;0.239257;,
  0.000000;0.000000;,
  0.024688;0.239257;,
  1.000000;0.239257;,
  0.024688;0.000000;,
  1.000000;0.000000;,
  0.000000;0.239257;,
  0.000000;0.000000;,
  0.975312;0.730067;,
  0.000000;0.730067;,
  0.975312;1.000000;,
  0.000000;1.000000;,
  1.000000;0.730067;,
  1.000000;1.000000;,
  0.024688;1.000000;,
  0.000000;1.000000;,
  0.000000;0.730067;,
  0.024688;0.730067;,
  1.000000;0.730067;,
  1.000000;1.000000;;
 }
}
