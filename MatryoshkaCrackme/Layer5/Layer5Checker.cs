using System;
using System.Linq;
using System.Reflection;

namespace Layer5 {
    public class Layer5Checker {
        public static bool IsValid(string username, string licenseKey) {
            var assembly = Assembly.Load(Properties.Resources.Layer6);
            var type = assembly.GetTypes().Where(t => t.Name.Equals("Layer6Checker")).First();
            var isValidFunction = type.GetMethod("IsValid");
            return (bool)isValidFunction?.Invoke(null, new object[] { username, licenseKey });
        }
    }
}
