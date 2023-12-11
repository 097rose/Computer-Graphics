#include <stdio.h>
#include <stdlib.h>
#include <map>
#include <vector>
#include <string>
#include <iostream>
#include <fstream>
#include <sstream>
#include <regex>
#include <glm/glm.hpp>

using namespace std;

class Object
{
public:
	vector<float> positions;
	vector<float> normals;
	vector<float> texcoords;

	Object(const char* obj_file)
	{
		std::vector< unsigned int > vertexIndices, uvIndices, normalIndices;
		vector<glm::vec3> tmp_vertices;
		vector<glm::vec3> tmp_normals;
		vector<glm::vec2> tmp_texcoords;

		regex wTexture_3(" [0-9]+/[0-9]+/[0-9]+ [0-9]+/[0-9]+/[0-9]+ [0-9]+/[0-9]+/[0-9]+\n");
		regex woTexture_3(" [0-9]+//[0-9]+ [0-9]+//[0-9]+ [0-9]+//[0-9]+\n");

		FILE* file = fopen(obj_file, "r");
		if (file == NULL)
		{
			cout << "Can't open obj file!\n";
			return;
		}

		while (true)
		{
			char lineHead[512];
			int res = fscanf(file, "%s", lineHead);
			if (res == EOF)
			{
				break;
			}
			if (strcmp(lineHead, "v") == 0)
			{
				glm::vec3 vertex;
				fscanf(file, "%f %f %f\n", &vertex.x, &vertex.y, &vertex.z);
				tmp_vertices.push_back(vertex);
			}
			else if (strcmp(lineHead, "vn") == 0)
			{
				glm::vec3 normal;
				fscanf(file, "%f %f %f\n", &normal.x, &normal.y, &normal.z);
				tmp_normals.push_back(normal);
			}
			else if (strcmp(lineHead, "vt") == 0) {
				glm::vec2 uv;
				fscanf(file, "%f %f\n", &uv.x, &uv.y);
				tmp_texcoords.push_back(uv);
			}
			else if (strcmp(lineHead, "f") == 0)
			{
				char f_line[128];
				int vertexIndex[3], uvIndex[3], normalIndex[3];
				fgets(f_line, sizeof(f_line), file);

				if (regex_match(f_line, wTexture_3))
				{
					sscanf(f_line, "%d/%d/%d %d/%d/%d %d/%d/%d\n", &vertexIndex[0], &uvIndex[0], &normalIndex[0], &vertexIndex[1], &uvIndex[1], &normalIndex[1], &vertexIndex[2], &uvIndex[2], &normalIndex[2]);
				}
				else if (regex_match(f_line, woTexture_3))
				{
					sscanf(f_line, "%d//%d %d//%d %d//%d\n", &vertexIndex[0], &normalIndex[0], &vertexIndex[1], &normalIndex[1], &vertexIndex[2], &normalIndex[2]);
					uvIndex[0] = -1;
					uvIndex[1] = -1;
					uvIndex[2] = -1;
				}

				//int matches = fscanf(file, "%d/%d/%d %d/%d/%d %d/%d/%d\n", &vertexIndex[0], &uvIndex[0], &normalIndex[0], &vertexIndex[1], &uvIndex[1], &normalIndex[1], &vertexIndex[2], &uvIndex[2], &normalIndex[2]);
				//if (matches != 9) {
				//	printf("File can't be read by our simple parser : ( Try exporting with other options\n");
				//	cout << "matches= " << matches << endl;
				//	return;
				//}

				vertexIndices.push_back(vertexIndex[0]);
				vertexIndices.push_back(vertexIndex[1]);
				vertexIndices.push_back(vertexIndex[2]);
				uvIndices.push_back(uvIndex[0]);
				uvIndices.push_back(uvIndex[1]);
				uvIndices.push_back(uvIndex[2]);
				normalIndices.push_back(normalIndex[0]);
				normalIndices.push_back(normalIndex[1]);
				normalIndices.push_back(normalIndex[2]);
			}
		}

		for (unsigned int i = 0; i < vertexIndices.size(); i++)
		{
			unsigned int vertexIndex = vertexIndices[i];
			glm::vec3 vertex = tmp_vertices[vertexIndex - 1];
			positions.push_back(vertex.x);
			positions.push_back(vertex.y);
			positions.push_back(vertex.z);

			vertexIndex = uvIndices[i];
			if (vertexIndex != -1)
			{
				glm::vec2 uv = tmp_texcoords[vertexIndex - 1];
				texcoords.push_back(uv.x);
				texcoords.push_back(uv.y);
			}
			else
			{
				texcoords.push_back(0);
				texcoords.push_back(0);
			}

			vertexIndex = normalIndices[i];
			glm::vec3 normal = tmp_normals[vertexIndex - 1];
			normals.push_back(normal.x);
			normals.push_back(normal.y);
			normals.push_back(normal.z);
		}
	}
};