Step 1: Setting Up Google Sheets
Create a new Google Sheet:

Go to Google Sheets and create a new spreadsheet.
Name your spreadsheet (e.g., "ESP32 Data").
Set up Google Sheets API:

Go to the Google Cloud Console.
Create a new project (if you don't have one).
Navigate to the APIs & Services > Library.
Enable the Google Sheets API and Google Drive API.
Create Service Account Credentials:

Go to APIs & Services > Credentials.
Click on Create Credentials and choose Service Account.
Fill in the required fields and create a key in JSON format.
Download the JSON key file. You will need to convert this key to a format that your ESP32 can use.
Share your Google Sheet with the service account email (something like your-service-account@your-project.iam.gserviceaccount.com) with edit permissions.
Step 2: Setting Up Your ESP32
Install Arduino IDE and Libraries:

Make sure you have the Arduino IDE installed.
Install the necessary libraries:
WiFi
HTTPClient
ArduinoJson
Prepare the JSON key:

Open your JSON key file and find the client_email and private_key fields.
You'll use these credentials in your ESP32 code.
Step 3: ESP32 Code
Here is a sample code that reads an analog value from pin A0 and sends it to Google Sheets:


Step 4: Google Apps Script
Create a Google Apps Script:
Open your Google Sheet.
Go to Extensions > Apps Script.
Delete any existing code and paste the following code:
javascript
Copy code
function doGet(e) {
  var sheet = SpreadsheetApp.getActiveSpreadsheet().getActiveSheet();
  var value = e.parameter.value;
  sheet.appendRow([new Date(), value]);
  return ContentService.createTextOutput("Success");
}
Deploy the script as a web app:
Click on the deploy button (near the top right) > New deployment.
Select Web app.
Under Execute as, choose Me.
Under Who has access, choose Anyone.
Click Deploy and authorize the script.
Copy the Deployment ID from the resulting dialog. This will be used as google_script_id in your ESP32 code.
Step 5: Run the Code
Upload the code to your ESP32 using the Arduino IDE.
Open the Serial Monitor to see the debug messages.
You should see the analog values being sent to your Google Sheet every 10 seconds.
