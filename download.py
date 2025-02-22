import os
import requests
import zipfile

# Function to download the selected asset
def download_asset(download_url, output_path):
    print(f"Downloading {output_path}...")
    response = requests.get(download_url)
    with open(output_path, 'wb') as f:
        f.write(response.content)
    print("Download completed.")

# Function to extract the zip file
def extract_zip(zip_path, destination_folder):
    print(f"Extracting {zip_path}...")
    with zipfile.ZipFile(zip_path, 'r') as zip_ref:
        zip_ref.extractall(destination_folder)
    print("Extraction completed.")

# Function to list the available assets from the GitHub release
def list_assets(owner, repo):
    url = f"https://api.github.com/repos/{owner}/{repo}/releases/latest"
    response = requests.get(url)
    release_data = response.json()
    
    assets = release_data.get('assets', [])
    
    if not assets:
        print("No assets found in the latest release.")
        return None
    
    print("Available assets:")
    for i, asset in enumerate(assets, 1):
        print(f"{i}. {asset['name']}")
    
    return assets

def main():
    # GitHub repository details
    owner = "coop-deluxe"  # Replace with the repository owner's username
    repo = "sm64coopdx"  # Replace with the repository name
    
    # List the assets
    assets = list_assets(owner, repo)
    if not assets:
        return
    
    # Ask the user to select an asset
    selection = int(input(f"Enter the number of the asset you want to download (1 to {len(assets)}): "))
    
    if selection < 1 or selection > len(assets):
        print("Invalid selection. Please choose a valid number.")
        return
    
    selected_asset = assets[selection - 1]
    download_url = selected_asset['browser_download_url']
    file_name = selected_asset['name']
    
    # Define the output path (same directory as the script)
    current_directory = os.getcwd()
    output_path = os.path.join(current_directory, file_name)
    
    # Download the selected asset
    download_asset(download_url, output_path)
    
    # If the downloaded file is a zip file, extract it
    if file_name.endswith('.zip'):
        extract_zip(output_path, current_directory)
    
    # Remove the zip file after extraction
    os.remove(output_path)
    print("Cleanup completed.")

if __name__ == "__main__":
    main()
import os
import requests
import zipfile

# Function to download the selected asset
def download_asset(download_url, output_path):
    print(f"Downloading {output_path}...")
    response = requests.get(download_url)
    with open(output_path, 'wb') as f:
        f.write(response.content)
    print("Download completed.")

# Function to extract the zip file
def extract_zip(zip_path, destination_folder):
    print(f"Extracting {zip_path}...")
    with zipfile.ZipFile(zip_path, 'r') as zip_ref:
        zip_ref.extractall(destination_folder)
    print("Extraction completed.")

# Function to list the available assets from the GitHub release
def list_assets(owner, repo):
    url = f"https://api.github.com/repos/{owner}/{repo}/releases/latest"
    response = requests.get(url)
    release_data = response.json()
    
    assets = release_data.get('assets', [])
    
    if not assets:
        print("No assets found in the latest release.")
        return None
    
    print("Available assets:")
    for i, asset in enumerate(assets, 1):
        print(f"{i}. {asset['name']}")
    
    return assets

def main():
    # GitHub repository details
    owner = "username"  # Replace with the repository owner's username
    repo = "repository"  # Replace with the repository name
    
    # List the assets
    assets = list_assets(owner, repo)
    if not assets:
        return
    
    # Ask the user to select an asset
    selection = int(input(f"Enter the number of the asset you want to download (1 to {len(assets)}): "))
    
    if selection < 1 or selection > len(assets):
        print("Invalid selection. Please choose a valid number.")
        return
    
    selected_asset = assets[selection - 1]
    download_url = selected_asset['browser_download_url']
    file_name = selected_asset['name']
    
    # Define the output path (same directory as the script)
    current_directory = os.getcwd()
    output_path = os.path.join(current_directory, file_name)
    
    # Download the selected asset
    download_asset(download_url, output_path)
    
    # If the downloaded file is a zip file, extract it
    if file_name.endswith('.zip'):
        extract_zip(output_path, current_directory)
    
    # Remove the zip file after extraction
    os.remove(output_path)
    print("Cleanup completed.")

if __name__ == "__main__":
    main()
