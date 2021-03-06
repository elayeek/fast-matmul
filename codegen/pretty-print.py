#   Copyright (c) 2014-2015, Sandia Corporation
#   All rights reserved.
#
#   This file is part of fast-matmul and is under the BSD 2-Clause License, 
#   which can be found in the LICENSE file in the root directory, or at 
#   http://opensource.org/licenses/BSD-2-Clause.

import sys, numpy

'''
This script converts coefficients in codegen style and outputs triplets of matrices
    * this script assumes square dimensions
    * it prints transpose of 3rd matrix following Brent equations

The usage is:
   python pretty-print.py coeff_file dimension rank

where

coeff_file is the name of the original coefficient file
m,k,n is the original algorithm dimensions
'''

def read_coeffs(filename):
    ''' Read the coefficient file.  There is one group of coefficients for each
    of the three matrices.  Keep the textual structure of the file. '''
    coeffs = []
    with open(filename, 'r') as coeff_file:
        curr_group = []
        for line in coeff_file:
            if line[0] == '#':
                if len(curr_group) > 0:
                    coeffs.append(curr_group)
                    curr_group = []
            else:
                curr_group.append([val for val in line.split()])
    coeffs.append(curr_group)
    return coeffs

def main():
    try:
        coeff_file = sys.argv[1]
        dim  = int(sys.argv[2])
        rank = int(sys.argv[3])
        print 'Printing coefficients for a %d x %d x %d rank-%d algorithm\n' % (dim,dim,dim,rank)
    except:
        raise Exception('USAGE: python pretty-print.py coeff_file dimension rank')

    coeffs = read_coeffs(coeff_file)
    # There should be three sets of coefficients: one for each matrix.
    if (len(coeffs) != 3):
        raise Exception('Expected three sets of coefficients!')
        
    for triplet in xrange(rank):
        print 'Triplet %d:' % (triplet+1)    	
        for i in xrange(dim):
            for fac in xrange(3):
            	sys.stdout.write('\t')
                for j in xrange(dim):
                    ''' print transpose of W matrices '''
                    if fac == 2:
                        rc_ind = i+dim*j
                    else:
                        rc_ind = i*dim+j
                    c = int(coeffs[fac][rc_ind][triplet])
                    ''' print space before nonnegative numbers '''
                    if c >= 0:
                        sys.stdout.write(' ')
                    sys.stdout.write('%s ' % c)
            sys.stdout.write('\n')
        sys.stdout.write('\n')
	
	''' count how many matrices of each rank are in factors '''	
    rc = [0] * dim
    for i in xrange(dim):
    	rc[i] = [0] * dim
    	for j in xrange(dim):
    	    rc[i][j] = [0]* dim
    rs = [0,0,0]
    for triplet in xrange(rank):
        for fac in xrange(3):
            facmat = zip(*coeffs[fac])
            A = numpy.matrix(facmat[triplet]).reshape(dim,dim)
            rs[fac] = numpy.linalg.matrix_rank(A)
        rc[rs[0]-1][rs[1]-1][rs[2]-1] += 1
    
    ''' count nnz in solution '''
    nnz = 0
    for fac in xrange(3):
        for col in xrange(rank):
           for row in xrange(dim*dim):
               if int(coeffs[fac][row][col]) != 0:
                   nnz = nnz + 1

	
    print 'Triplets rank counts'
    for i in xrange(dim):
        for j in xrange(dim):
            for k in xrange(dim):
                if rc[i][j][k] > 0:
                    print '\tRank (%d,%d,%d):\t%d' % (i+1,j+1,k+1,rc[i][j][k])
        
    print '\nTotal number of nonzeros:\t%d' % nnz
    print 'Number of naive adds/subs:\t%d' % int(nnz-2*rank-dim*dim)
    print '\n'

if __name__ == '__main__':
    main()
