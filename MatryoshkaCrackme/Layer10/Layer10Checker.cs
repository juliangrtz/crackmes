using System;
using System.Linq;
using System.Security.Cryptography;
using System.Text;

namespace Layer10 {
    public class Layer10Checker {
        private static readonly string SecretKey = "crackmes.onecrackmes.onecrackmes";

        public static bool IsValid(string username, string license) {
            string hashedUsername = ComputeSha256Hash(username);
            string encryptedHash = EncryptString(hashedUsername, SecretKey);
            return encryptedHash.Equals(license, StringComparison.OrdinalIgnoreCase);
        }

        private static string ComputeSha256Hash(string rawData) {
            using (SHA256 sha256Hash = SHA256.Create()) {
                byte[] bytes = sha256Hash.ComputeHash(Encoding.UTF8.GetBytes(rawData));
                StringBuilder builder = new StringBuilder();

                for (int i = 0; i < bytes.Length; i++)
                    builder.Append(bytes[i].ToString("x2"));

                return builder.ToString().ToUpper();
            }
        }

        private static string EncryptString(string text, string key) {
            using (Aes aesAlg = Aes.Create()) {
                aesAlg.Key = Encoding.UTF8.GetBytes(key);
                aesAlg.GenerateIV();
                aesAlg.Mode = CipherMode.ECB;

                ICryptoTransform encryptor = aesAlg.CreateEncryptor(aesAlg.Key, aesAlg.IV);
                byte[] encrypted = encryptor.TransformFinalBlock(Encoding.UTF8.GetBytes(text), 0, text.Length);
                return BitConverter.ToString(encrypted.Take(16).ToArray()).Replace("-", "").Substring(0, 20);
            }
        }
    }
}

