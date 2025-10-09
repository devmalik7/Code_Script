# Checks if websites are online or offline.

import requests
import argparse

def check_website(url):
    try:
        response = requests.get(url, timeout=5)
        if response.status_code == 200:
            print(f"✅ {url} is UP")
        else:
            print(f"⚠️ {url} returned status code {response.status_code}")
    except requests.RequestException:
        print(f"❌ {url} is DOWN or unreachable")

if __name__ == "__main__":
    parser = argparse.ArgumentParser(description="Check if websites are online.")
    parser.add_argument("urls", nargs="+", help="One or more website URLs to check.")
    args = parser.parse_args()
    for site in args.urls:
        if not site.startswith(("http://", "https://")):
            site = "http://" + site
        check_website(site)
