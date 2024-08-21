using System.Media;
using System.Text.RegularExpressions;
using System.Threading;
using System.Windows.Forms;

namespace MatryoshkaCrackme {

    public partial class Form : System.Windows.Forms.Form {

        private SoundPlayer soundPlayer;

        public Form() {
            InitializeComponent();

            new Thread(() => {
                soundPlayer = new SoundPlayer(Properties.Resources.CosmicMindWave);
                soundPlayer.Play();
            }).Start();
        }

        private void RegisterBtn_Click(object sender, System.EventArgs e) {
            var username = UsernameTxtBx.Text;
            var licenseKey = LicTxtBx1.Text + LicTxtBx2.Text + LicTxtBx3.Text + LicTxtBx4.Text;

            if (username.Length < 5) {
                ShowErrorMessage("Username must be at least 5 characters long.");
                return;
            }

            if (licenseKey.Length != 20 || !Regex.IsMatch(licenseKey, @"^[A-Za-z0-9]{20}$")) {
                ShowErrorMessage("License key is invalid. It must be a 20-character alphanumeric string.");
                return;
            }

            var licenseChecker = new LicenseChecker();
            if (licenseChecker.IsValid(username, licenseKey)) {
                soundPlayer.Stop();
                MessageBox.Show("Registration successful.", "Success", MessageBoxButtons.OK, MessageBoxIcon.Information);
                Application.Exit();
            } else {
                ShowErrorMessage("The license you provided is invalid.");
            }

        }

        #region UI Stuff

        private void ShowErrorMessage(string message)
            => MessageBox.Show(message, "Error", MessageBoxButtons.OK, MessageBoxIcon.Error);

        private void Form_FormClosing(object sender, FormClosingEventArgs e) {
            Application.Exit();
        }

        private void LicTxtBx1_TextChanged(object sender, System.EventArgs e) {
            if (LicTxtBx1.Text.Length == LicTxtBx1.MaxLength)
                LicTxtBx2.Focus();
        }

        private void LicTxtBx2_TextChanged(object sender, System.EventArgs e) {
            if (LicTxtBx2.Text.Length == LicTxtBx2.MaxLength)
                LicTxtBx3.Focus();
        }

        private void LicTxtBx3_TextChanged(object sender, System.EventArgs e) {
            if (LicTxtBx3.Text.Length == LicTxtBx3.MaxLength)
                LicTxtBx4.Focus();
        }

        #endregion UI Stuff
    }
}