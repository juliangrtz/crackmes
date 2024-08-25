using System;
using System.Linq;
using System.Reflection;

namespace Layer7 {
    public class Layer7Checker {
        public static bool IsValid(string username, string licenseKey) {
            var assembly = Assembly.Load(Properties.Resources.Layer8);
            var type = assembly.GetTypes().Where(t => t.Name.Equals("Layer8Checker")).First();
            var isValidFunction = type.GetMethod("IsValid");
            return (bool)isValidFunction?.Invoke(null, new object[] { username, licenseKey });
        }
    }
}
