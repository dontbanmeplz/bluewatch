from flask import Flask, request, jsonify
import os
app = Flask(__name__)

@app.route('/all', methods=['GET'])
def get():
    files = os.listdir('data/app')
    return ','.join(files)

@app.route('/s/<path:filename>', methods=['GET'])
def re(filename):
    try:
        with open(os.path.join('data/app', filename), 'r') as file:
            return file.read()
    except FileNotFoundError:
        return "File not found", 404

if __name__ == '__main__':
    app.run(host='0.0.0.0',port=8080,debug=True)
