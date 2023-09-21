import os
import sys
import glob
from pathlib import Path
from io import StringIO


dbc_directory = sys.argv[1]

includes = StringIO()
inits = StringIO()


def frame2Bus(frame_name):
    if 'Mid3' in frame_name:
        return 'A'
    if 'Mid5' in frame_name:
        return 'B'
    if 'Mid6' in frame_name:
        return 'C'
    raise Exception('Unknown bus!')


for frame in sorted(glob.glob(os.path.join(dbc_directory, "*.h"))):
    frame_name = Path(frame).stem
    includes.write('#include "DBC/{}.h"\n'.format(frame_name))
    inits.write('{}_Init(frame_ids_{bus}, frames_info_{bus}, signalgroups_info_{bus}, signals_info_{bus});\n'.format(frame_name, bus=frame2Bus(frame_name)))


print(includes.getvalue())
print(inits.getvalue());

