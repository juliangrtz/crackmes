using System.Security.Cryptography;
using System.Text;

namespace KeyGenerator {
    internal class Program {
        private static readonly string SecretKey = "crackmes.onecrackmes.onecrackmes";

        static void Main() {
            Console.Write("Username: ");
            var username = Console.ReadLine() ?? "";

            string hashedUsername = ComputeSha256Hash(username);
            string license = EncryptString(hashedUsername, SecretKey);

            Console.WriteLine($"License key: {license}");
        }

        private static string ComputeSha256Hash(string rawData) {
            byte[] bytes = SHA256.HashData(Encoding.UTF8.GetBytes(rawData));
            StringBuilder builder = new();

            for (int i = 0; i < bytes.Length; i++)
                builder.Append(bytes[i].ToString("x2"));

            return builder.ToString().ToUpper();
        }

        private static string EncryptString(string text, string key) {
            using Aes aesAlg = Aes.Create();
            aesAlg.Key = Encoding.UTF8.GetBytes(key);
            aesAlg.GenerateIV();
            aesAlg.Mode = CipherMode.ECB;

            ICryptoTransform encryptor = aesAlg.CreateEncryptor(aesAlg.Key, aesAlg.IV);
            byte[] encrypted = encryptor.TransformFinalBlock(Encoding.UTF8.GetBytes(text), 0, text.Length);
            return BitConverter.ToString(encrypted[..16]).Replace("-", "")[..20];
        }
    }
}
