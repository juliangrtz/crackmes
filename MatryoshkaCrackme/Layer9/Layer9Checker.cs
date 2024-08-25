using System;
using System.Linq;
using System.Reflection;

namespace Layer9 {
    public class Layer9Checker {
        public static bool IsValid(string username, string licenseKey) {
            var assembly = Assembly.Load(Properties.Resources.Layer10);
            var type = assembly.GetTypes().Where(t => t.Name.Equals("Layer10Checker")).First();
            var isValidFunction = type.GetMethod("IsValid");
            return (bool)isValidFunction?.Invoke(null, new object[] { username, licenseKey });
        }
    }
}
