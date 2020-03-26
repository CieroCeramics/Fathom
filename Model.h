//This class deals with ONLY the loading, drawing and transformation of models

#pragma once

#include "Vector3f.h"
#include "Matrix.h"
#include "Texture.h"
//#include "Shader.h"
//#include "Animation.h"
//#include "Timer.h"
//#include "Text.h"
//#include "Skeleton.h"
//#include "Skin.h"
//#include "animationPlayer.h"
//#include "Path.h"

#include <string>
#include <vector>
#include <sstream> //String stream
#include <fstream> //File stream

#define NG_BOX_COLLISION 0
#define NG_CIRCLE_COLLISION 1 //2D collision, just the circle on the ground
#define NG_PILL_COLLISION 2 //Same as above, but covers for the height of the object

#define NG_COLLISION_DETECTION_THRESHOLD 25

#define NG_NO_HIT -1
#define NG_HIT_LEFT 0 //			UP
#define NG_HIT_RIGHT 1 //		 _________
#define NG_HIT_TOP 2 //			 [		 ]
#define NG_HIT_BOTTOM 3 //	LEFT [  TOP  ] RIGHT		And then naturally the other side of top is bottom
#define NG_HIT_UP 4 //			 [_______]
#define NG_HIT_DOWN 5 //			DOWN
#define NG_HIT 6

#define NG_OBJ 0
#define NG_OBJS 1

#define NG_2D 0
#define NG_3D 1

#define NG_VERTEX 0
#define NG_NORMAL 1
#define NG_TEXTURE 2
#define NG_TANGENT 3
#define NG_BITANGENT 4

#define NG_NO_LINK 0 //No link
#define NG_LINK_ABOVE 1 //Always stay above the model you are linked to

#define NG_BACKFACE_CULLING 1
#define NG_FRONTFACE_CULLING 2

class Model
{
public:
	Model();
	Model(const std::string &directory, const std::string fileName, unsigned int type); //Constructor that auto calls the load function
	Model(const std::string &directory, const std::string modelName, unsigned int type, char* textureName); //Constructor that auto calls both load functions
	~Model();

	void initVariables();
	void initDrawBuffers();

	void loadOBJ(const std::string &directory, const std::string &fileName); //Loads obj data
	void loadOBJS(const std::string &directory, const std::string &fileName);
	void setTexture(unsigned int index, Texture *texture);
	void setModelName(const std::string &fileName);
	std::string getModelName();	
	std::string getTextureName(unsigned int num);

	void setPosition(Vector3f &position);	
	void setSpawnPoint(Vector3f &position);
	void setVelocity(Vector3f velocity);
	void setAccel(Vector3f &accel);
	void setSpeed(float speed);
	void setScale(Vector3f &scale);
	void setColor(float r, float g, float b, float a);
	void setRotate(Vector3f angle);
	void setActive(bool status);

	void setLink(Model *model, unsigned int type);

	Vector3f getPosition();
	Vector3f getAdjustedPosition(); //NOTE RIGHT NOW THIS DOES NOT ACCOUNT FOR MOVING OBJECTS.
	Vector3f getSpawnPoint();	
	Vector3f getVelocity();	
	Vector3f getAccel();	
	float getSpeed();	
	Vector3f getScale();
	float getColor(unsigned int index);
	Vector3f getRotate();
	Vector3f getModelSize();
	Vector3f getMinSize();
	Vector3f getMaxSize();
	float getRadius(unsigned int type);
	bool getActive();
	
	void increaseScale(Vector3f &scale);
	void updateSize(Vector3f &newPoint);
	
	void setAnimation(unsigned int animation, float weight);

	void setMesh(float* vertex, unsigned int &vertexSize, 
				 float* normal, unsigned int &normalSize, 
				 float* texture, unsigned int &textureSize,
				 Vector3f &minSize, Vector3f &maxSize,
				 std::string name);

	void setMesh(Model &model);
	float* getMesh(unsigned int type);
	unsigned int& getMeshSizes(unsigned int type);
	float* getMeshIndices();
	unsigned int getMeshIndicesSize();
	unsigned int getMeshFaceNum();

	//void setShader(int shader, const char* shaderFile, const char* newShader);
	//Shader* getShader(int shader);
	//void shaderParameterHandler(Shader* shader);

	//void setNotificationStuff(Text** text, Timer** timer);

	static void setLightPos(Vector3f &pos, unsigned int index);
	static Vector3f getLightPos(unsigned int index);
	static unsigned int getMaxLights();
	static void setEyePos(Vector3f &pos);
	static Vector3f getEyePos();
	static void initLight(Vector3f &pos, Vector3f &color);	
	static void setGlobalLightIntensity(float intensity);
	static float getGlobalLightIntensity();
	static void setLightMatrix();

	int hitTest(Model &model, unsigned int type);
	void setHitSize(float size);
	float getHitSize();

	//void setLanded(bool state);
	//bool getLanded();
	//void setPlatform(int index);
	//int getPlatform();

	//void enableCollisionDetection();
	//void disableCollisionDetection();
	//bool getCollisionDetection(); //Terrible name.

	//Mesh Skinning
	//void setSkeleton(Skeleton &skeleton);
	//void setSkin(Skin &skin);
	//void setupSkeleton();
	//void startAnimationTimer();
	//void updateAnimation();
	//playerAnimations* getSkeletonAnimation();

	void setLightingCharacteristics(float ke, float ka, float ks, float kd, float shininess);
	void setUVOffset(float offset);
	float getUVOffset();

	//Path* getPath();

	void transform(); //Does all the model transformations and stores it. Makes the draw function cleaner.
	void draw(unsigned int culling, bool wireframe, bool shaderOn); //Draws model if it is loaded in
	void drawBoundingBox();
	void drawBoundingSphere();

	void updateLink();
	void update(float &time);
	
	bool _shaderToggle[4]; //Toggles for random toggles for shaders
	//Timer* timer; //TEMP. Totally used for the owned thing.

protected:
	struct triangle //Triangles store vertices. Each vertex represents an index in this case
	{
		int v1;
		int v2;
		int v3;
	};

	struct vertex //Tbh pretty much like the Vector3f class, but this is simpler/lazier
	{
		float x;
		float y;
		float z;
	};

	struct colorInfo //Four "colors"
	{
		float r;
		float g;
		float b;
		float a;
	} _color;

	void _sortArrays(std::vector<triangle> &faceTemp, std::vector<triangle> &faceNormalTemp, std::vector<triangle> &faceTextureTemp, 
					 std::vector<vertex> &vertexTemp, std::vector<vertex> &vertexNormalTemp, std::vector<vertex> &vertexTextureTemp);
	void _generateBuffers();
	void _setupTangents(std::vector<triangle> &faceTemp, std::vector<triangle> &faceNormalTemp, std::vector<triangle> &faceTextureTemp, 
					    std::vector<vertex> &vertexTemp, std::vector<vertex> &vertexNormalTemp, std::vector<vertex> &vertexTextureTemp);
	void _calcTangent(vertex &p1, vertex &p2, vertex &p3, vertex &t1, vertex &t2, vertex &t3, unsigned int index);

	float* _vertexInfo;
	float* _vertexNormalInfo;
	float* _vertexTextureInfo;
	float* _vertexIndex;
	float* _tangentInfo;
	float* _bitangentInfo;

	unsigned int _numOfVertices;
	unsigned int _numOfVerticesNormal;
	unsigned int _numOfVerticesTexture;
	unsigned int _numFaces;

	//std::string _MODELS_PATH;

	Texture _texture[4]; //Stores texture information. Max of four

	std::string _modelName;

	Vector3f _spawnPoint;
	Vector3f _previousPosition; //The previous frame's position
	Vector3f _position; //The draw position
	Vector3f _adjustedPosition; //The actual position of the object keeping in mind the maya translations. Used right now for spherical collision
	Vector3f _velocity;
	Vector3f _acceleration;
	float _speed;	

	Vector3f _scale;
	Vector3f _rotate;

	Matrix transformations;

	float _hitSize;

	///Shader* _vShader;
	//Shader* _fShader;

	static std::vector<Vector3f> _lightPos;
	static std::vector<Vector3f> _lightColor;
	static const unsigned int _MAX_LIGHTS = 4;
	static Vector3f _eyePos;
	static float _globalLightIntensity;
	static float _lightModelViewMatrix[16];
	static float _lightProjectionMatrix[16];
	static float _lightModelViewProjectionMatrix[16];
	static Matrix* _reallyHackyLightModelViewProjectionMatrix;

	GLuint _buffer;
	GLuint _texBuffer;
	GLuint _normBuffer;
	GLuint _tangentBuffer;
	GLuint _bitangentBuffer;

	Vector3f _modelSizeMax; //The loaded obj max size
	Vector3f _modelSizeMin; //The loaded obj min size
	Vector3f _adjustedModelSizeMax; //Accounts for scale
	Vector3f _adjustedModelSizeMin; //Accounts for scale

	//Animation _animation;

	//HIT TEST VARIABLES
	Vector3f _lineStartHT;
	Vector3f _lineEndHT;
	Vector3f _lineHT;
	float _leftHT;
	float _rightHT;
	float _upHT;
	float _downHT;

	//The info needed for if the model is linked with another model
	Model* _link;
	unsigned int _linkType;

	//Mesh Skinning
	//Skeleton* _skeleton;
	//Skin* _skin;
	//Timer* _animationTimer;
	//playerAnimations* _skeletonAnimation;

	//Lighting and shader stuff
	float _ke;
	float _ka;
	float _ks;
	float _kd;
	float _shininess;
	float _uvOffset;

	//MISC
	//Text** _notificationText;
	//Timer** _notificationTimer;
	//unsigned int _notificationCounter;
	
	//Path* _path;

	//MAYBE TEMP
	//bool _landed; //TOTALLY TEMP
	//int _currentPlatform; //Contains the index of which platform you are on
	//bool _doCollisionDetection; //The switch that controls whether or not the object is colliding with platforms
	bool _active; //Whether or not we want this thing to be drawn/calculated for
};
