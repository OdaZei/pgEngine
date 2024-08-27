#include <SFML/Graphics/Image.hpp>
#include <SFML/Graphics/Rect.hpp>

#include "include/ResourcesManager.hpp"
#include "include/filepaths.hpp"

SpriteSheet::SpriteSheet( ): defSprWidth(_DEFAULT_TEXTURE_WIDTH_), defSprHeight(_DEFAULT_TEXTURE_HEIGHT_)\
,tWidth(_DEFAULT_SPRITESHEET_W_),tHeight(_DEFAULT_SPRITESHEET_H_), filepath(spriteSheet2), mTexture(nullptr){
    mTexture = new sf::Texture( );
    tiles = std::vector<std::vector<Tile*>>();
    if(!mTexture->loadFromFile(filepath)) printf( "Empty spritesheet texture\n" );
}
SpriteSheet::SpriteSheet( std::vector<std::vector<int>> arr, int w, int h ): defSprWidth(_DEFAULT_TEXTURE_WIDTH_), defSprHeight(_DEFAULT_TEXTURE_HEIGHT_)\
,tWidth(w),tHeight(h), filepath(spriteSheet2), mTexture(nullptr) {
    mTexture = new sf::Texture();
    setTileMap(arr);
    computeMap( arr );
    //loadResources(arr);
}
void SpriteSheet::setTileMap( std::vector<std::vector<int>> arr ){
    tiles.clear();
    int i, j = 0;
    for( auto& ar: arr ){
        j = 0;
        std::vector<Tile*> T;
        for( auto& a: ar){
            bool col = false;
            if( a >= 23 && a < 38)
                col = true;
            Tile* t = new Tile( a, i, j, false, col );
            T.push_back(t);
            j++;
        }
        i++;
        tiles.push_back(T);
    }
}
SpriteSheet::~SpriteSheet(){ }
bool SpriteSheet::computeMap( std::vector<std::vector<int>> arr ) {
    std::vector<int> corners(9,-1);
    // Arr changes with each iteration on double for loop L:30; storing for base comparation;
    std::vector<std::vector<int>> cpy;
    cpy = arr;
    /*
        0 1 2
        3 4 5
        6 7 8
    */
    int sr , cmp, opt, cr = 0;
    
    for( unsigned int i = 1; i < tWidth ; i++ ){
        for( unsigned int j = 1; j < tHeight; j++ ){
            
            sr = arr[i][j];
            //Set center of corners to current tile;
            corners[4] = arr[i][j];
            // Check borders of array;
            
            if( i == 0 && j == 0 ) {
                corners[5] = cpy[i+1][j];
                corners[7] = cpy[i][j+1];
                corners[8] = cpy[i+1][j+1];
            }else if( i == tWidth - 1 && j == tHeight - 1) {
                corners[1] = cpy[i][j-1];
                corners[3] = cpy[i-1][j];
                corners[0] = cpy[i-1][j-1];
            }else if( i == tWidth - 1 ) {
                corners[1] = cpy[i][j-1];
                corners[0] = cpy[i-1][j-1];
                corners[3] = cpy[i-1][j];
                corners[6] = cpy[i-1][j+1];
                corners[7] = cpy[i][j+1];
            }else if( j == tHeight - 1 ) {
                corners[1] = cpy[i][j-1];
                corners[0] = cpy[i-1][j-1];
                corners[3] = cpy[i-1][j];
                corners[2] = cpy[i+1][j-1];
                corners[5] = cpy[i+1][j];
            } else if(  j == 0){
                corners[3] = cpy[i-1][j];
                corners[5] = cpy[i+1][j];
                corners[6] = cpy[i-1][j+1];
                corners[7] = cpy[i][j+1];
                corners[8] = cpy[i+1][j+1];
            }else if( i == 0 ){
                corners[1] = cpy[i][j-1];
                corners[2] = cpy[i+1][j-1];
                corners[5] = cpy[i+1][j];
                corners[7] = cpy[i][j+1];
                corners[8] = cpy[i+1][j+1];
            }else {
                // Not on arr border
                corners[0] = cpy[i-1][j-1];
                corners[1] = cpy[i][j-1];
                corners[3] = cpy[i-1][j];
                corners[2] = cpy[i+1][j-1];
                corners[5] = cpy[i+1][j];
                corners[6] = cpy[i-1][j+1];
                corners[7] = cpy[i][j+1];
                corners[8] = cpy[i+1][j+1];
            }
            //using cross sections on coordinates; 0 2 6 8
            //normalized sections on coordinates:  1 3 5 7
            /*
             *
             * 0   1  2  3  4  5  6  7  8  9 10 11 12 13 14 15
             * 16 17 18 19 20 21 22 23 24 25 26 27 28 29 30 31 
             * 32 33 34 35 36 37 38 39 40 41 42 43 44 45 46 47
             * 48 .   .  .  .  .  .  .  .  .  .  .  .  .  .  .
             * 
             * array holds the index of the default texture enviroment, water , grass , dirt , stone
             * only compares each tile with smaller index env.
             */
            if( (corners[1] < sr  ) && (corners[5] < sr ) && (corners[3] < sr )){
                // T L R D
                if( corners[7] < sr )
                    arr[i][j] = sr + 34;
                else
                    arr[i][j] = sr + 31; // T L R
            }else if( (corners[7] < sr  ) && (corners[5] < sr   ) && (corners[3] < sr   ) ){
                // D L R
                arr[i][j] = sr + 33;
            }else if ( (corners[1] < sr   ) && (corners[7] < sr   ) && (corners[5] < sr   ) ){
                // TOP DOWN RIGHT
                arr[i][j] = sr + 32 ;
            }else if( (corners[1] < sr  ) && (corners[7] < sr ) && (corners[3] < sr  ) ){
                // TOP DOWN LEFT
                arr[i][j] = sr + 30;
            }else if( (corners[1] < sr  ) && (corners[3] < sr   ) ){ 
                // TOP LEFT
                arr[i][j] = sr-17;
            }else if( (corners[1] < sr  ) && (corners[5] < sr )){
                // TOP RIGHT
                arr[i][j] = sr-15;
            }else if( (corners[7] < sr   ) && (corners[3] < sr)){
                // DOWN LEFT
                arr[i][j] = sr+15;
            }else if( (corners[7] < sr  ) && (corners[5] < sr  ) ){
                // DOWN RIGHT
                arr[i][j] = sr+17;
            }else if((corners[3] < sr  ) && (corners[5] < sr  )) {
                arr[i][j] = sr+18;
            }else if((corners[7] < sr  ) && (corners[1] < sr  )) {
                arr[i][j] = sr+19;
            }else if( corners[1] < sr  ){
                // TOP
                arr[i][j] = sr-16;
            }else if( corners[7] < sr ){
                // DOWN
                arr[i][j] = sr+16;
            }else if( corners[3] < sr){
                // LEFT
                arr[i][j] = sr-1;
            }else if( corners[5] < sr  ){
                // RIGHT
                arr[i][j] = sr+1;
            }else if( corners[0] < sr  ){
                // diagonalal top left;
                arr[i][j] = sr+3;
            }else if( corners[2] < sr   ){
                // diagonalal top right;
                arr[i][j] = sr+2;
            }
            else if( corners[6] < sr  ){
                // diagonalal down left;
                arr[i][j] = sr-13;
            }else if( corners[8] < sr ){
                // diagonal down right;
                arr[i][j] = sr-14;
            }
        }
    }
    loadResources(arr);
    return true;
}
sf::VertexArray SpriteSheet::getVertex( int _x, int _y, int tx, int ty ) {
    int x = _x - (defSprWidth/2);
    int y = _y - (defSprHeight/2);
    sf::VertexArray va;
    va.setPrimitiveType(sf::Triangles);
    va.resize(nTriangles*defSprWidth);
    sf::Vertex* triangles = &va[nTriangles];

    triangles[0].position = sf::Vector2f(x , y );
    triangles[1].position = sf::Vector2f((x + defSprWidth) , y );
    triangles[2].position = sf::Vector2f(x , (y + defSprHeight));
    triangles[3].position = sf::Vector2f(x , (y + defSprHeight));
    triangles[4].position = sf::Vector2f((x + defSprWidth) , y);
    triangles[5].position = sf::Vector2f((x + defSprWidth) , (y + defSprHeight) );

    triangles[0].texCoords = sf::Vector2f(tx * defSprWidth, ty * defSprHeight);
    triangles[1].texCoords = sf::Vector2f((tx + 1) * defSprWidth, ty * defSprHeight);
    triangles[2].texCoords = sf::Vector2f(tx * defSprWidth, (ty + 1) * defSprHeight);
    triangles[3].texCoords = sf::Vector2f(tx * defSprWidth, (ty + 1) * defSprHeight);
    triangles[4].texCoords = sf::Vector2f((tx + 1) * defSprWidth, ty * defSprHeight);
    triangles[5].texCoords = sf::Vector2f((tx + 1) * defSprWidth, (ty + 1) * defSprHeight);
   
    return va;
}
//need to template 
bool SpriteSheet::loadResources( std::vector<std::vector<int>> arr) {
    int nTiles = 16;
    if(!mTexture->loadFromFile(filepath)) return false;
    mVertex.setPrimitiveType(sf::Triangles);
    mVertex.resize( nTriangles * tWidth * tHeight);
    for( unsigned int i = 0; i < tWidth ; i++ ){
        for( unsigned int j = 0; j < tHeight; j++ ){
            int tile = arr[i][j];
            int tx = tile % nTiles;
            int ty = tile / nTiles;
            sf::Vertex* triangles  = &mVertex[(i + j*tWidth)*nTriangles];
            triangles[0].position  = sf::Vector2f(i * defSprWidth, j * defSprHeight);
            triangles[1].position  = sf::Vector2f((i + 1) * defSprWidth, j * defSprHeight);
            triangles[2].position  = sf::Vector2f(i * defSprWidth, (j + 1) * defSprHeight);
            triangles[3].position  = sf::Vector2f(i * defSprWidth, (j + 1) * defSprHeight);
            triangles[4].position  = sf::Vector2f((i + 1) * defSprWidth, j * defSprHeight);
            triangles[5].position  = sf::Vector2f((i + 1) * defSprWidth, (j + 1) * defSprHeight);

            triangles[0].texCoords = sf::Vector2f(tx * defSprWidth, ty * defSprHeight);
            triangles[1].texCoords = sf::Vector2f((tx + 1) * defSprWidth, ty * defSprHeight);
            triangles[2].texCoords = sf::Vector2f(tx * defSprWidth, (ty + 1) * defSprHeight);
            triangles[3].texCoords = sf::Vector2f(tx * defSprWidth, (ty + 1) * defSprHeight);
            triangles[4].texCoords = sf::Vector2f((tx + 1) * defSprWidth, ty * defSprHeight);
            triangles[5].texCoords = sf::Vector2f((tx + 1) * defSprWidth, (ty + 1) * defSprHeight);
        }
    }
    return true;
}
//CAlled By WorldManager to retrieve the closest 8 tiles + position;
std::vector<int> SpriteSheet::getnearestTiles(int x, int y, std::vector<Tile*>& ts){
    std::vector<int> corners( 9 , 0 );
    int cX = tWidth / 2;
    int cY = tHeight / 2;
    int p = 0;
    if(x < 0 || y < 0 ) return corners;
    for( int j = -1 ; j <= 1; j++){
        for( int i = -1 ; i <= 1; i++ ){
            ts.push_back( tiles[cX+i][cY+j] );
            corners[p] = tiles[cX+i][cY+j]->getId();
            p++;
        }
    }
    return corners;

}
void SpriteSheet::update( std::vector<std::vector<int>> arr , int w, int h ) {
    tWidth = w;
    tHeight = h;
    computeMap(arr);
}
sf::VertexArray SpriteSheet::getTiles( ) {
    return mVertex;
}
bool SpriteSheet::setTextureSlice( int x, int y, unsigned int& index, int tile ){
    bool success = false;

    int tx, ty = 0;
    tx = tile % 16;
    ty = tile / 16;

    long int sz = mBuffers.size() - 1;
    sf::VertexArray tmpArr = getVertex( x , y , tx , ty );
    
    if( tmpArr.getVertexCount( ) > 0 )
        success = true;
    
    if( success ) {
        mBuffers.push_back( tmpArr );
        index = mBuffers.size() - 1;
        if(index != 0 )
            printf( "Got vertex index\n" );
    }
    
    return success;
}
sf::VertexArray SpriteSheet::getTextureSlice( unsigned int index ) {
    if( index >= 0 && index < mBuffers.size() )
        return mBuffers[index];

    return mBuffers[mBuffers.size()-1];
}
std::vector<sf::VertexArray> SpriteSheet::setAnimationSlice(int x, int y, unsigned int& index, int tile, unsigned int animSz ){
    unsigned int tmp = 0;

    std::vector<sf::VertexArray> vctarr;
    
    for( unsigned int i = 0; i < animSz; i++ ){
        if(!setTextureSlice( x , y , tmp, tile + i ))
            printf( "Resources_Error: Could not load texture: Fn() = setAnimationSlice()\n" );
        vctarr.push_back( getTextureSlice( tmp ) );
    }
    
    index = tmp;
    return vctarr;
}
sf::Texture* SpriteSheet::getTexture( ) {
    return mTexture;
}

