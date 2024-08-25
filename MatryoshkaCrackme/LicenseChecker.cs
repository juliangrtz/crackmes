using System.Linq;
using System.Reflection;

namespace MatryoshkaCrackme {
    internal class LicenseChecker {
        public object GetTheFuckOutOfHere = new object();

        public LicenseChecker() {

        }

        public bool IsValid(string username, string licenseKey) {
            var assembly = Assembly.Load(Properties.Resources.Layer0);
            var type = assembly.GetTypes().Where(t => t.Name.Equals("Layer0Checker")).First();
            var isValidFunction = type.GetMethod("IsValid");

            return (bool)isValidFunction?.Invoke(null, new[] { username, licenseKey });
        }
    }
}
