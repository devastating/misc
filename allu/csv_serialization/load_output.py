import numpy as np
import struct
import sys

COL_STRUCT = "!l"
DOUBLE_STRUCT = "!d"


def load_from(file):
    '''
    Load into pynum matrix
    '''
    matrix = []
    with open(file, "r") as fd:
        col_struct = struct.Struct(COL_STRUCT)
        double_struct = struct.Struct(DOUBLE_STRUCT)
        # First get rows
        val = fd.read(col_struct.size)
        col = col_struct.unpack(val)
        col = col[0]
        print "Col: ", col
        this_row = 0
        row_array = []
        while True:
            val = fd.read(double_struct.size)
            if len(str(val)) < 8:
                break
            double_val = double_struct.unpack(val)
            this_row += 1
            row_array.append(double_val[0])
            if this_row == (col - 1):
                # We don't save first col (timestamp)
                this_row = 0
                matrix.append(tuple(row_array))
                row_array = []
    return np.array(matrix)


def main():
    if len(sys.argv) != 2:
        print "Usage:", __file__, "<path of binary to load>"
        raise Exception
    load_from("output.bin")

if __name__ == "__main__":
    try:
        main()
    except Exception:
        sys.exit(1);
