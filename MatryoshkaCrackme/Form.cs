using System.IO.Compression;
using System.IO;
using System.Media;
using System.Runtime.InteropServices;
using System.Text.RegularExpressions;
using System.Threading;
using System.Windows.Forms;
using MatryoshkaCrackme.Properties;
using System;
using System.Diagnostics;

namespace MatryoshkaCrackme {

    public partial class Form : System.Windows.Forms.Form {
        private SoundPlayer soundPlayer;

        [DllImport("kernel32.dll", SetLastError = true, CharSet = CharSet.Unicode)]
        public static extern bool IsDebuggerPresent();

        public Form() {
            new Thread(() => {
                while (true) {
                    if (Debugger.IsAttached || IsDebuggerPresent()) {
                        var youShallNotDebug = new object();
                        GC.KeepAlive(youShallNotDebug);
                        Environment.Exit(-1);
                    }
                }
            }).Start();

            InitializeComponent();

            new Thread(() => {
                var bytes = new MemoryStream();
                Resources.Cosmic_Mind.CopyTo(bytes);
                var decompressed = Decompress(bytes.ToArray());
                var memoryStream = new MemoryStream(decompressed);

                soundPlayer = new SoundPlayer(memoryStream);
                soundPlayer.PlayLooping();
            }).Start();
        }

        private void RegisterBtn_Click(object sender, System.EventArgs e) {
            var username = UsernameTxtBx.Text;
            var licenseKey = LicTxtBx1.Text + LicTxtBx2.Text + LicTxtBx3.Text + LicTxtBx4.Text;

            if (username.Length < 5 || !Regex.IsMatch(licenseKey, @"^[A-Za-z0-9]{20}$")) {
                ShowErrorMessage("Username must be at least 5 characters long and an alphanumeric string.");
                return;
            }

            if (licenseKey.Length != 20 || !Regex.IsMatch(licenseKey, @"^[A-Za-z0-9]{20}$")) {
                ShowErrorMessage("License key must be a 20-character alphanumeric string.");
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
            soundPlayer.Stop();
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

        //private static byte[] Compress(byte[] data) {
        //    using (var compressedStream = new MemoryStream())
        //    using (var zipStream = new GZipStream(compressedStream, CompressionMode.Compress)) {
        //        zipStream.Write(data, 0, data.Length);
        //        zipStream.Close();
        //        return compressedStream.ToArray();
        //    }
        //}

        private static byte[] Decompress(byte[] data) {
            using (var compressedStream = new MemoryStream(data))
            using (var zipStream = new GZipStream(compressedStream, CompressionMode.Decompress))
            using (var resultStream = new MemoryStream()) {
                zipStream.CopyTo(resultStream);
                return resultStream.ToArray();
            }
        }

        private void LicTxtBx1_KeyDown(object sender, KeyEventArgs e) {
            bool ctrlV = e.Modifiers == Keys.Control && e.KeyCode == Keys.V;
            bool shiftIns = e.Modifiers == Keys.Shift && e.KeyCode == Keys.Insert;

            if (ctrlV || shiftIns) {
                var clipboardContent = Clipboard.GetText();

                if (clipboardContent.Length >= 20) {
                    LicTxtBx1.Clear();
                    LicTxtBx2.Clear();
                    LicTxtBx3.Clear();
                    LicTxtBx4.Clear();

                    LicTxtBx1.Text = clipboardContent.Substring(0, 5);
                    LicTxtBx2.Text = clipboardContent.Substring(5, 5);
                    LicTxtBx3.Text = clipboardContent.Substring(10, 5);
                    LicTxtBx4.Text = clipboardContent.Substring(15, 5);
                }
            }
        }
    }
}