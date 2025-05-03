from django.urls import path
from . import views

urlpatterns = [
    path("dashboard/", views.web_interface, name="web_interface"),
    path("api/firebase/", views.firebase_api, name="firebase_api"),
]
