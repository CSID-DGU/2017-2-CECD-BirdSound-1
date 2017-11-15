#include "stdafx.h"
#include "textureing.cpp"
#include "colorIO.cpp"

int main(int argc, char** argv)
{

	// read mesh from plyfile
	PCL_INFO("\nLoading mesh from file %s...\n", argv[1]);
	pcl::PolygonMesh triangles;
	pcl::io::loadPolygonFile(argv[1], triangles);

	pcl::PointCloud<pcl::PointXYZ>::Ptr cloud(new pcl::PointCloud<pcl::PointXYZ>);
	pcl::fromROSMsg(triangles.cloud, *cloud);

	// Create the texturemesh object that will contain our UV-mapped mesh
	TextureMesh mesh;
	mesh.cloud = triangles.cloud;
	std::vector< pcl::Vertices> polygon_1;

	// push faces into the texturemesh object
	polygon_1.resize(triangles.polygons.size());
	for (size_t i = 0; i < triangles.polygons.size(); ++i)
	{
		polygon_1[i] = triangles.polygons[i];
	}
	mesh.tex_polygons.push_back(polygon_1);
	PCL_INFO("\tInput mesh contains %d faces and %d vertices\n", mesh.tex_polygons[0].size(), cloud->points.size());
	PCL_INFO("...Done.\n");

	// Load textures and cameras poses and intrinsics
	PCL_INFO("\nLoading textures and camera poses...\n");
	pcl::texture_mapping::CameraVector my_cams;

	const boost::filesystem::path base_dir(".");
	std::string extension(".txt");
	int cpt_cam = 0;
	for (boost::filesystem::directory_iterator it(base_dir); it != boost::filesystem::directory_iterator(); ++it)
	{
		if (boost::filesystem::is_regular_file(it->status()) && boost::filesystem::extension(it->path()) == extension)
		{
			pcl::TextureMapping<pcl::PointXYZ>::Camera cam;
			readCamPoseFile(it->path().string(), cam);
			cam.texture_file = boost::filesystem::basename(it->path()) + ".png";
			my_cams.push_back(cam);
			cpt_cam++;
		}
	}
	PCL_INFO("\tLoaded %d textures.\n", my_cams.size());
	PCL_INFO("...Done.\n");

	// Display cameras to user
	PCL_INFO("\nDisplaying cameras. Press \'q\' to continue texture mapping\n");
	showCameras(my_cams, cloud);


	// Create materials for each texture (and one extra for occluded faces)
	mesh.tex_materials.resize(my_cams.size() + 1);
	for (int i = 0; i <= my_cams.size(); ++i)
	{
		pcl::TexMaterial mesh_material;
		mesh_material.tex_Ka.r = 0.2f;
		mesh_material.tex_Ka.g = 0.2f;
		mesh_material.tex_Ka.b = 0.2f;

		mesh_material.tex_Kd.r = 0.8f;
		mesh_material.tex_Kd.g = 0.8f;
		mesh_material.tex_Kd.b = 0.8f;

		mesh_material.tex_Ks.r = 1.0f;
		mesh_material.tex_Ks.g = 1.0f;
		mesh_material.tex_Ks.b = 1.0f;

		mesh_material.tex_d = 1.0f;
		mesh_material.tex_Ns = 75.0f;
		mesh_material.tex_illum = 2;

		std::stringstream tex_name;
		tex_name << "material_" << i;
		tex_name >> mesh_material.tex_name;

		if (i < my_cams.size())
			mesh_material.tex_file = my_cams[i].texture_file;
		else
			mesh_material.tex_file = "occluded.jpg";

		mesh.tex_materials[i] = mesh_material;
	}


	// Sort faces
	PCL_INFO("\nSorting faces by cameras...\n");
	pcl::TextureMapping<pcl::PointXYZ> tm; // TextureMapping object that will perform the sort
	tm.textureMeshwithMultipleCameras(mesh, my_cams);


	PCL_INFO("Sorting faces by cameras done.\n");
	for (int i = 0; i <= my_cams.size(); ++i)
	{
		PCL_INFO("\tSub mesh %d contains %d faces and %d UV coordinates.\n", i, mesh.tex_polygons[i].size(), mesh.tex_coordinates[i].size());
	}


	// compute normals for the mesh
	PCL_INFO("\nEstimating normals...\n");
	pcl::NormalEstimation<pcl::PointXYZ, pcl::Normal> n;
	pcl::PointCloud<pcl::Normal>::Ptr normals(new pcl::PointCloud<pcl::Normal>);
	pcl::search::KdTree<pcl::PointXYZ>::Ptr tree(new pcl::search::KdTree<pcl::PointXYZ>);
	tree->setInputCloud(cloud);
	n.setInputCloud(cloud);
	n.setSearchMethod(tree);
	n.setKSearch(20);
	n.compute(*normals);

	// Concatenate XYZ and normal fields
	pcl::PointCloud<pcl::PointNormal>::Ptr cloud_with_normals(new pcl::PointCloud<pcl::PointNormal>);
	pcl::concatenateFields(*cloud, *normals, *cloud_with_normals);
	PCL_INFO("...Done.\n");

	pcl::toROSMsg(*cloud_with_normals, mesh.cloud);

	PCL_INFO("\nSaving mesh to textured_mesh.obj\n");

	saveOBJFile("textured_mesh.obj", mesh, 5);

	return (0);
}