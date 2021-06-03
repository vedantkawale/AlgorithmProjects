///////////////////////////////////////////////////////////////////////////////
// crossing_algs.hpp
//
// Algorithms that solve the iceberg avoiding problem.
//
// All of the TODO sections for this project reside in this file.
//
// This file builds on ices_types.hpp, so you should familiarize yourself
// with that file before working on this file.
//
///////////////////////////////////////////////////////////////////////////////

#pragma once

#include <cassert>
#include <iostream>

#include "ices_types.hpp"

namespace ices {
// Solve the iceberg avoiding problem for the given grid, using an exhaustive
// optimization algorithm.
//
// This algorithm is expected to run in exponential time, so the grid's
// width+height must be small enough to fit in a 64-bit int; this is enforced
// with an assertion.
//
// The grid must be non-empty.
unsigned int iceberg_avoiding_exhaustive(const grid& setting) {
 clock_t begin_time = clock();
  // grid must be non-empty.
  assert(setting.rows() > 0);
  assert(setting.columns() > 0);

  // Compute the path length, and check that it is legal.
  const size_t steps = setting.rows() + setting.columns() - 2;
  assert(steps < 64);

  unsigned int count_paths = 0;
    
  // TODO: implement the exhaustive optimization algorithm, then delete this
  // comment.
//std::cout << steps;
//int step1=pow(2,steps);
//std::cout << step1;
//std::cout << "This ";
size_t pathCount=pow(2,steps);
 size_t c=0,r=0,bit=0,k;
//std::cout << pathCount;
  for (size_t i = 0; i < pathCount; ++i)
{
	c=0;r=0;
	for(k = 0;k<steps ; k++)
	{
		bit=(int)(i/(pow(2,k)));
		bit=bit & 1;
		//std::cout << bit;
		if(bit==1)	
		{
		c++;
		}
		else if(bit==0)
		{
		r++;
		}
		//std::cout <<(bool)setting.get(r,c);
		
		
		if(r<setting.rows() && c<setting.columns())
		{
			if(setting.get(r,c)==ices::CELL_ICEBERG)
			{
			break;
			}
		}
	}
	
	if(k==steps && r<setting.rows()   &&  c<setting.columns()  )
	{
	
	count_paths++;
	}
}
//std::cout<<count_paths;	
  return count_paths;
}

// Solve the iceberg avoiding problem for the given grid, using a dynamic
// programming algorithm.
//
// The grid must be non-empty.
unsigned int iceberg_avoiding_dyn_prog(const grid& setting) {

  // grid must be non-empty.
  assert(setting.rows() > 0);
  assert(setting.columns() > 0);


  const int DIM=100;
  std::vector<std::vector<unsigned>> A(DIM, std::vector<unsigned>(DIM));

  A[0][0] = 1;
    size_t From_above,From_left;
  // TODO: implement the dynamic programming algorithm, then delete this
  // comment.
  for(size_t i=0;i<setting.rows();i++)
	{
	for(size_t j=0;j<setting.columns();j++)
		{
		if(i==0 && j==0)
		continue;
		else if(setting.get(i,j)==ices::CELL_ICEBERG)
			{
			//std::cout<<"in iceberg";
			A[i][j]=0;
			}
		else
		{
		//std::cout<<"Inside the fun";
		From_above=0;
		From_left=0;
		if(j>0 && A[i][j-1]!=0)
		{
			//std::cout<<"inside from left";
			From_left=A[i][j-1];
		}
		if(i>0 && A[i-1][j]!=0)
		{
			//std::cout<<"right";
			From_above=A[i-1][j];
		}
		
		
		if(From_left==0 && From_above==0)	
			{
			A[i][j]=0;
			
			}
		else
		A[i][j]=From_left+From_above;
		}
		}	
	}
  return A[setting.rows()-1][setting.columns()-1];
}

}
