using System.Linq;
using System.Reflection;

namespace Layer2 {
    public class Layer2Checker {
        public static bool IsValid(string username, string licenseKey) {
            var assembly = Assembly.Load(Properties.Resources.Layer3);
            var type = assembly.GetTypes().Where(t => t.Name.Equals("Layer3Checker")).First();
            var isValidFunction = type.GetMethod("IsValid");
            return (bool)isValidFunction?.Invoke(null, new object[] { username, licenseKey });
        }
    }
}
