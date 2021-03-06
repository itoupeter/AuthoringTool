﻿
#include "BodyReshaper.h"
#include "../AutomaticRigging/pinocchioApi.h"

#include <maya/MGlobal.h>
#include <maya/MArgDatabase.h>
#include <fstream>
#include <ios>

const char *BodyReshaper::fileFlag = "-f";
const char *BodyReshaper::fileLongFlag = "-file";

BodyReshaper::BodyReshaper() : MPxCommand() {

}

BodyReshaper::~BodyReshaper() {

}

void* BodyReshaper::creator(){ 
	
	return new BodyReshaper(); 
}

MSyntax BodyReshaper::newSyntax(){

	MSyntax syntax;

	syntax.addFlag( fileFlag, fileLongFlag, MSyntax::kString );  //文件名
	
	return syntax;
}

MStatus BodyReshaper::doIt( const MArgList& args ){

	MArgDatabase argData( syntax(), args ); //get the database of the arguments 调用一个command
	MString filename;
	
	if( argData.isFlagSet( fileFlag ) ) //数据库有没有提供这个参数 -f，有-f就取出-f后面跟着的值
		argData.getFlagArgument( fileFlag, 0, filename ); // -f , filename 

	cout << "Automatic rigging: " << filename << endl;

	Mesh mesh( filename.asChar() );
	RotateMesh( mesh );
	Skeleton skeleton = HumanSkeleton();
	PinocchioOutput output = autorig( skeleton, mesh );

	for( int i = 0; i < ( int )output.embedding.size(); ++i ){

		MString createJointCmd( "joint -p " );

		//output.embedding[ i ] = ( output.embedding[ i ] - mesh.toAdd ) / mesh.scale;
		output.embedding[ i ] = ( output.embedding[ i ] - Vector3( .5, .5, .5 ) ) * 2./* + Vector3( 0., 0., 1. )*/;
		createJointCmd = createJointCmd 
			+ output.embedding[ i ][ 0 ] + " " 
			+ output.embedding[ i ][ 1 ] + " "
			+ output.embedding[ i ][ 2 ] + " "
			+ " -n joint" + i + "; select -cl;";

		MGlobal::executeCommand( createJointCmd );
	}

	MString parentJointCmd = 
		"jointDisplayScale 0.1; ikHandleDisplayScale 0.2;\n"
		"select -r joint1; select -tgl joint0; parent;\n"
		"select -r joint2; select -tgl joint1; parent;\n"
		"select -r joint3; select -tgl joint0; parent;\n"
		"select -r joint4; select -tgl joint2; parent;\n"
		"select -r joint5; select -tgl joint4; parent;\n"
		"select -r joint6; select -tgl joint5; parent;\n"
		"select -r joint7; select -tgl joint6; parent;\n"
		"select -r joint8; select -tgl joint2; parent;\n"
		"select -r joint9; select -tgl joint8; parent;\n"
		"select -r joint10; select -tgl joint9; parent;\n"
		"select -r joint11; select -tgl joint10; parent;\n"
		"select -r joint12; select -tgl joint0; parent;\n"
		"select -r joint13; select -tgl joint12; parent;\n"
		"select -r joint14; select -tgl joint13; parent;\n"
		"select -r joint15; select -tgl joint0; parent;\n"
		"select -r joint16; select -tgl joint15; parent;\n"
		"select -r joint17; select -tgl joint16; parent;\n"
		"select -r joint0; select -tgl body:Mesh; SmoothBindSkin;\n"
		"setAttr skinCluster1.normalizeWeights 0;\n"
		"ikHandle -sj joint4 -ee joint6;\n"
		"ikHandle -sj joint8 -ee joint10;\n"
		"ikHandle -sj joint12 -ee joint14;\n"
		"ikHandle -sj joint15 -ee joint17;\n";

	MGlobal::executeCommand( parentJointCmd );

	for( int i = 0; i < ( int )mesh.vertices.size(); ++i ){ //6000多个顶点

		Vector< double, -1 > v = output.attachment->getWeights(i);   //第i个顶点对应每个Joint的权重
		vector< double > weights( v.size() + 1, 0 );    //只有17个骨头，18个Joints。
		vector< int > parent{ 0, 0, 1, 0, 2, 4, 5, 6, 2, 8, 9, 10, 0, 12, 13, 0, 15, 16 };  // 0-17的对应的Parent
		MString jointWeightCmd;

		jointWeightCmd = jointWeightCmd  
			+ "select -r body:Mesh.vtx["
			+ i
			+ "]; skinPercent -normalize false -zeroRemainingInfluences true ";

		for( int j = 0; j < v.size(); ++j ) {  //17个骨头

			double d = floor( 0.5 + v[j] * 10000. ) / 10000.;

			weights[ j + 1 ] += d * .5;   //分成两个Joint 
			weights[ parent[ j + 1 ] ] += d * .5;
		}

		for( int j = 0; j < weights.size(); ++j ){
			jointWeightCmd = jointWeightCmd + "-transformValue joint" + j + " " + weights[ j ] + " ";
		} //18个Joint的weight给顶点。 一个顶点每个joint对它造成的影响。

		jointWeightCmd = jointWeightCmd + "skinCluster1;";
		MGlobal::executeCommand( jointWeightCmd );
	}
	
	return MStatus::kSuccess;
}

void BodyReshaper::RotateMesh( Mesh &mesh ){

	Quaternion<> transform( Vector3( 1., 0., 0 ), -90. * M_PI / 180. );

	for( auto &e : mesh.vertices ){
		e.pos = transform * e.pos;
	}

	mesh.normalizeBoundingBox();
	mesh.computeVertexNormals();
}
