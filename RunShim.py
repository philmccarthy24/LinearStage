import os
import time
#from pywinauto import application
from flask import Flask, request, Response
import flask
import json

### Launch Drive controller software

#need to be in same dir for this to work!
#os.chdir(r'C:\Program Files\Parker\EasiV')
#easiv_app = application.Application()
#easiv_app.start(r'EASIV.EXE')
#prodSelDlg = easiv_app['Product selection']
#prodSelDlg['ViX500IH or ViX250IH intelligent servo drive + linear motor'].Click()
#prodSelDlg['OK'].Click()

### Kick off web service
app = Flask(__name__)

@app.route('/')
@app.route('/<path:filename>')
def index(filename='index.html'):
	scriptdir = os.path.dirname(os.path.realpath(__file__))
	print("scriptdir: {0}, request: {1}".format(scriptdir, filename))
	return flask.send_from_directory(scriptdir, filename)

@app.route('/api/position', methods=['GET', 'PUT'])
def position():
	if request.method == 'PUT':
		putObj = request.get_json()
		print("test " + json.dumps(putObj))
		# do something with put data here...
		return Response(status=204) # 204 is OK no content
	else:
		return "Not implemented"

if __name__ == '__main__':
    app.run()