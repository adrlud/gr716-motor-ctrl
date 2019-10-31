
import plotly.graph_objects as go
import pandas as pd
import numpy as np
import os
from os import path


renamee = '/home/adrian/logg-1572452926.csv'


df = pd.read_csv(renamee)
#/x = np.arange(df.count)




fig = go.Figure( data=go.Scatter(x = df.timedelta - df.timedelta[1], y=(((50*1000*1000)/df.timestamp)*60), line_shape = 'spline', ))

fig.update_layout(title='BLDC-motor',
                   xaxis_title='Millisekunder',
                   yaxis_title='RPM',
                   yaxis_range = [0, 4000],
                
                   )

fig.show()
