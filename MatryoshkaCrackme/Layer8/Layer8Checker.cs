using System;
using System.Linq;
using System.Reflection;

namespace Layer8 {
    public class Layer8Checker {
        public static bool IsValid(string username, string licenseKey) {
            var assembly = Assembly.Load(Properties.Resources.Layer9);
            var type = assembly.GetTypes().Where(t => t.Name.Equals("Layer9Checker")).First();
            var isValidFunction = type.GetMethod("IsValid");
            return (bool)isValidFunction?.Invoke(null, new object[] { username, licenseKey });
        }
    }
}
