from flask import Flask, make_response, render_template, request
app = Flask(__name__)

from solver import solve

@app.route('/')
def index():
    return render_template('index.html', name='Seb')

@app.route('/solve')
def solution():
    out = solve()
    response = make_response(out.getvalue())
    response.mimetype = 'image/png'
    print(request.args.get('selected-img'))
    return response
