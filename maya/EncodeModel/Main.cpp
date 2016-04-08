
#include "EncodeModel.h"

#include <iostream>
using std::cout;
using std::endl;

#include <fstream>
using std::fstream;

#include <ios>
using std::ios;

void saveData(){

	fstream fin( "in.txt", ios::in );
	fstream fout( "out.txt", ios::out );
	vector< int > v;
	int a;

	for( int i = 0; i < 12894 * 3; ++i ){
		fin >> a;
		v.push_back( a );
	}
	
	for( int i = 0; i < 12894; ++i ){
		fout << v[ i ] << " " << v[ i + 12894 ] << " " << v[ i + 25788 ] << endl;
	}
}

void testEncode(){

	fstream fout( "out.txt", ios::out );
	MatrixXd vertices;
	MatrixXi faces;
	MatrixXd temp;
	MatrixXd neigh;

	ReadObj( "test.obj", vertices, faces );
	temp = LoadTemplate();
	neigh = LoadNeighbor();


}

int main(){

	testEncode();

	return 0;
}