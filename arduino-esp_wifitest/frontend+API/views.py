import requests
from django.http import JsonResponse
from django.shortcuts import render

# Firebase Realtime Database URL (no trailing slash)
FIREBASE_DB_URL = "https://your-project-id.firebaseio.com"

# View for JSON API
def firebase_api(request):
    url = f"{FIREBASE_DB_URL}/sensor/value.json"
    try:
        response = requests.get(url)
        response.raise_for_status()
        return JsonResponse({"value": response.json()})
    except requests.RequestException as e:
        return JsonResponse({"error": "Could not fetch data", "details": str(e)}, status=500)

# View for rendering the web interface
def web_interface(request):
    return render(request, "web_interface.html")
