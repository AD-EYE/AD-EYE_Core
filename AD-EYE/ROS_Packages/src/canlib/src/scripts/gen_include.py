import os
import sys
import glob
from pathlib import Path
from io import StringIO


dbc_directory = sys.argv[1]

includes = StringIO()
inits = StringIO()

for frame in sorted(glob.glob(os.path.join(dbc_directory, "*.h"))):
    frame_name = Path(frame).stem
    includes.write('#include "DBC/{}.h"\n'.format(frame_name))
    inits.write('{}_Init(g_frame_ids, g_frames_info, g_signalgroups_info, g_signals_info);\n'.format(frame_name))


print(includes.getvalue())
print(inits.getvalue());

