from flask import Flask, request, jsonify

app = Flask(__name__)

@app.route('/post-data', methods=['POST'])
def post_data():
    data = request.get_json()
    temperature = data['temperature']
    print(f"Received temperature: {temperature}°C")

    response = {"status": "success", "temperature": temperature}
    return jsonify(response), 200

if __name__ == '__main__':
    app.run(host='0.0.0.0', port=5000)
