using System;
using System.Linq;
using System.Reflection;

namespace Layer6 {
    public class Layer6Checker {
        public static bool IsValid(string username, string licenseKey) {
            var assembly = Assembly.Load(Properties.Resources.Layer7);
            var type = assembly.GetTypes().Where(t => t.Name.Equals("Layer7Checker")).First();
            var isValidFunction = type.GetMethod("IsValid");
            return (bool)isValidFunction?.Invoke(null, new object[] { username, licenseKey });
        }
    }
}
