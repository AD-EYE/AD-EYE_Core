

import pandas as pd 

list_of_points = pd.read_csv('point.csv', delimiter=',', header=None, skip_blank_lines=True,float_precision=None)

start_point = (list_of_points.loc[ [3],[4,5] ])
end_point = (list_of_points.loc[ [22],[4,5] ])
