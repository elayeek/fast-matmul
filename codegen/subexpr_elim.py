import convert
import sys

def all_pairs(col):
    ''' Return all pairs in column, where the column refers to the rank multiply.
    col is an array of coefficients. '''
    for i in range(len(col)):
        for j in range(i + 1, len(col)):
            if col[i] != '0' and col[j] != '0':
                yield ((col[i], col[j]), (i, j))


def can_substitute(val_pair1, val_pair2):
    ''' Returns true if and only if the two pairs can be replaced by a single multiply. 
    val1_pair1 and val_pair2 are pairs of coefficients
    '''
    try:
        val1a = float(val_pair1[0])
        val1b = float(val_pair1[1])
        val2a = float(val_pair2[0])
        val2b = float(val_pair2[1])
    except:
        return False

    # Can't match zeros
    if val2a == 0.0 or val2b == 0.0:
        return False

    scale1 = val1b / val1a
    scale2 = val2b / val2a

    if abs(scale1 - scale2) <= 1e-15:
        return True
        

def find_subexpression(pair, col):
    ''' Find occurence of the pair subexpression in the column.
    pair is of the form ((coeff1, coeff2), (ind1, ind2)) where coeff
         is a coefficient and ind is an index
    col is an array of coefficients such that we can access col[ind1], col[ind2]
    '''
    ind1, ind2 = pair[1]
    curr_val = (col[ind1], col[ind2])
    return can_substitute(pair[0], curr_val)


def eliminate(coeff_set, m, n):
    # Turn into column form
    rank = len(coeff_set[0])
    cols = [[x[i] for x in coeff_set] for i in range(rank)]
    match_dict = {}

    for i, col in enumerate(cols):
        for pair in all_pairs(col):
            for j in range(i + 1, len(cols)):
                if find_subexpression(pair, cols[j]):
                    # Hash the mapping by subcomputation (which multiply) where the subexpression originates
                    # and the index pair of the coefficients.
                    key = (i, pair[1][0], pair[1][1])
                    if key in match_dict:
                        match_dict[key].append(j)
                    else:
                        match_dict[key] = [j]

    remove_duplicates(match_dict)
    return sorted(match_dict.items(), key=lambda keyval: keyval[0])


def remove_duplicates(match_dict):
    ''' Remove duplicate eliminations from the match dictionary. '''
    # Sort by column (first) and index (second)
    sorted_matches = sorted(match_dict.iterkeys())
    keys_to_delete = []
    for key in sorted_matches:
        if len(match_dict[key]) > 1:
            for col_ind in match_dict[key][:-1]:
                keys_to_delete.append((col_ind, key[1], key[2]))

    for key in keys_to_delete:
        if key in match_dict:
            del match_dict[key]


def update_coeffs(coeff_set, elim_info):
    ''' Given the eliminations, create the new coefficients. '''
    def zero_col(col_ind, coeff_ind1, coeff_ind2):
        coeff_set[coeff_ind1][col_ind] = '0'
        coeff_set[coeff_ind2][col_ind] = '0'

    def get_scale(index, sub):
        ''' Get the scale factor for the substitution matrix. '''
        coeff_ind1, coeff_ind2 = index[1:3]
        col_ind = index[0]
        val1a = float(coeff_set[coeff_ind1][col_ind])
        val1b = float(coeff_set[coeff_ind1][sub])
        val2a = float(coeff_set[coeff_ind2][col_ind])
        val2b = float(coeff_set[coeff_ind2][sub])
        assert(0.0 not in [val1a, val1b, val2a, val2b])

        scale1 = val1b / val1a
        scale2 = val2b / val2a
        assert(abs(scale1 - scale2) <= 1e-15)

        return scale1

    rank = len(coeff_set[0])
    num_entries = len(coeff_set)
    for index, subs in elim_info:
        new_coeff_line = ['0'] * rank
        # In the multiply where the subexpression originates, replace with new matrix.
        new_coeff_line[index[0]] = '1'
        for sub in subs:
            # Replace the add with the substitute matrix.
            scale = get_scale(index, sub)
            new_coeff_line[sub] = scale
        coeff_set.append(new_coeff_line)

    # Get the additions needed to form the substitution matrices.
    all_sub_coeffs = []
    for index, subs in elim_info:
        sub_coeffs = ['0'] * num_entries
        sub_coeffs[index[1]] = coeff_set[index[1]][index[0]]
        sub_coeffs[index[2]] = coeff_set[index[2]][index[0]]
        all_sub_coeffs.append(sub_coeffs)
        
    # Zero out the columns
    for index, subs in elim_info:
        zero_col(index[0], index[1], index[2])
        for sub in subs:
            zero_col(sub, index[1], index[2])

    return all_sub_coeffs



def main():
    try:
        coeff_file = sys.argv[1]
        dims = tuple([int(d) for d in sys.argv[2].split(',')])
        print 'Reading coefficients for %d x %d x %d matrix' % dims
    except:
        raise Exception('USAGE: python subexpr_elim.py coeff_file m,k,n')

    coeffs = convert.read_coeffs(coeff_file)
    A_elim = eliminate(coeffs[0], dims[0], dims[1])
    B_elim = eliminate(coeffs[1], dims[0], dims[1])

    A_subs = update_coeffs(coeffs[0], A_elim)
    B_subs = update_coeffs(coeffs[1], B_elim)

    def num_elim(elim_info):
        return sum([len(subs) for index, subs in elim_info])

    total_elim = num_elim(A_elim) + num_elim(B_elim)
    print 'Eliminating %d non-zeros' % total_elim

    new_nonzeros = int(coeff_file.split('-')[-1]) - total_elim
    new_name = '-'.join(coeff_file.split('-')[:-1]) + '-%d' % (new_nonzeros)

    print 'Writing information to ' + new_name
    with open(new_name, 'w') as out_file:
        out_file.write('# Eliminated version of %s\n' % coeff_file)
        def write_coeff_set(coeff_set):
            ''' Write the coefficient set for a single matrix (A, B, or C). '''
            def pretty_print(value):
                if float(int(value)) == float(value):
                    return str(int(value))
                else:
                    return str(value)

            for entry in coeff_set:
                # Single (i, j) entry of a single matrix.
                out_file.write(' '.join([pretty_print(val) for val in entry]) + '\n')
     
        write_coeff_set(coeffs[0])
        out_file.write('#\n')
        write_coeff_set(coeffs[1])
        out_file.write('#\n')
        write_coeff_set(coeffs[2])
        out_file.write('# Substitution information\n')
        write_coeff_set(A_subs)
        out_file.write('#\n')
        write_coeff_set(B_subs)


if __name__ == '__main__':
    main()