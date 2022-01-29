
#pragma once

namespace MineTest {

    class Meshes;

    const int CHUNK_W = 16;
    const int CHUNK_H = 16;
    const int CHUNK_D = 16;
    const int CHUNK_VOL = CHUNK_W * CHUNK_H * CHUNK_D;
    
    struct Voxel;

    class Chunk {
    public:
        Chunk(int x, int y, int z);
        ~Chunk();


        bool m_modified;


    public:
        int m_x, m_y, m_z;
        Voxel* voxels;
    };

}
