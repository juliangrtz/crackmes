-- Generated by CSharp.lua Compiler
local System = System
local Linq = System.Linq.Enumerable
local SystemIO = System.IO
local ArrayByte = System.Array(System.Byte)
local Rew1nd
System.import(function (out)
  Rew1nd = out.Rew1nd
end)
System.namespace("ThouShallNotPass", function (namespace)
  namespace.class("Program", function (namespace)
    local Main
    Main = function ()
      local BitReverseTable = ArrayByte:new(256, { 0x00, 0x80, 0x40, 0xc0, 0x20, 0xa0, 0x60, 0xe0, 0x10, 0x90, 0x50, 0xd0, 0x30, 0xb0, 0x70, 0xf0, 0x08, 0x88, 0x48, 0xc8, 0x28, 0xa8, 0x68, 0xe8, 0x18, 0x98, 0x58, 0xd8, 0x38, 0xb8, 0x78, 0xf8, 0x04, 0x84, 0x44, 0xc4, 0x24, 0xa4, 0x64, 0xe4, 0x14, 0x94, 0x54, 0xd4, 0x34, 0xb4, 0x74, 0xf4, 0x0c, 0x8c, 0x4c, 0xcc, 0x2c, 0xac, 0x6c, 0xec, 0x1c, 0x9c, 0x5c, 0xdc, 0x3c, 0xbc, 0x7c, 0xfc, 0x02, 0x82, 0x42, 0xc2, 0x22, 0xa2, 0x62, 0xe2, 0x12, 0x92, 0x52, 0xd2, 0x32, 0xb2, 0x72, 0xf2, 0x0a, 0x8a, 0x4a, 0xca, 0x2a, 0xaa, 0x6a, 0xea, 0x1a, 0x9a, 0x5a, 0xda, 0x3a, 0xba, 0x7a, 0xfa, 0x06, 0x86, 0x46, 0xc6, 0x26, 0xa6, 0x66, 0xe6, 0x16, 0x96, 0x56, 0xd6, 0x36, 0xb6, 0x76, 0xf6, 0x0e, 0x8e, 0x4e, 0xce, 0x2e, 0xae, 0x6e, 0xee, 0x1e, 0x9e, 0x5e, 0xde, 0x3e, 0xbe, 0x7e, 0xfe, 0x01, 0x81, 0x41, 0xc1, 0x21, 0xa1, 0x61, 0xe1, 0x11, 0x91, 0x51, 0xd1, 0x31, 0xb1, 0x71, 0xf1, 0x09, 0x89, 0x49, 0xc9, 0x29, 0xa9, 0x69, 0xe9, 0x19, 0x99, 0x59, 0xd9, 0x39, 0xb9, 0x79, 0xf9, 0x05, 0x85, 0x45, 0xc5, 0x25, 0xa5, 0x65, 0xe5, 0x15, 0x95, 0x55, 0xd5, 0x35, 0xb5, 0x75, 0xf5, 0x0d, 0x8d, 0x4d, 0xcd, 0x2d, 0xad, 0x6d, 0xed, 0x1d, 0x9d, 0x5d, 0xdd, 0x3d, 0xbd, 0x7d, 0xfd, 0x03, 0x83, 0x43, 0xc3, 0x23, 0xa3, 0x63, 0xe3, 0x13, 0x93, 0x53, 0xd3, 0x33, 0xb3, 0x73, 0xf3, 0x0b, 0x8b, 0x4b, 0xcb, 0x2b, 0xab, 0x6b, 0xeb, 0x1b, 0x9b, 0x5b, 0xdb, 0x3b, 0xbb, 0x7b, 0xfb, 0x07, 0x87, 0x47, 0xc7, 0x27, 0xa7, 0x67, 0xe7, 0x17, 0x97, 0x57, 0xd7, 0x37, 0xb7, 0x77, 0xf7, 0x0f, 0x8f, 0x4f, 0xcf, 0x2f, 0xaf, 0x6f, 0xef, 0x1f, 0x9f, 0x5f, 0xdf, 0x3f, 0xbf, 0x7f, 0xff })

      local image0 = ArrayByte(0x89, 0x50, 0x4E, 0x47, 0x0D, 0x0A, 0x1A, 0x0A, 0x00, 0x00, 0x00, 0x0D, 0x49, 0x48, 0x44, 0x52, 0x00)

      local image17 = ArrayByte(0x00, 0x00, 0x7A, 0x00, 0x00, 0x00, 0x1C, 0x01, 0x03, 0x00, 0x00, 0x00, 0x94, 0x3A, 0x39, 0xE0, 0x00)

      local image34 = ArrayByte(0x00, 0x00, 0x06, 0x50, 0x4C, 0x54, 0x45, 0x15, 0x15, 0x15, 0xFE, 0xFE, 0xFE, 0x56, 0xDB, 0xD8, 0x4A)

      local image51 = ArrayByte(0x00, 0x00, 0x00, 0xE7, 0x49, 0x44, 0x41, 0x54, 0x78, 0x01, 0x35, 0xCF, 0xC7, 0x95, 0x13, 0x41, 0x00)

      local image68 = ArrayByte(0x05, 0xC0, 0x9A, 0x8F, 0xF7, 0x73, 0xDC, 0x1B, 0x43, 0x06, 0x64, 0x80, 0x4C, 0x42, 0x64, 0x40, 0x87)

      local image85 = ArrayByte(0x40, 0x28, 0x84, 0xB0, 0x2B, 0xE9, 0x4E, 0x0A, 0xAD, 0x23, 0xDE, 0x43, 0x8B, 0x37, 0x06, 0xBB, 0x95)

      local image102 = ArrayByte(0x41, 0x65, 0xF9, 0xE3, 0xD9, 0x72, 0xE9, 0x3C, 0xB0, 0x9C, 0xF3, 0x13, 0x10, 0x80, 0x86, 0xD3, 0xEA)

      local image119 = ArrayByte(0xAA, 0x18, 0xE0, 0x88, 0x93, 0xF6, 0x72, 0x92, 0x49, 0x33, 0xAB, 0xE5, 0xA3, 0xD6, 0x7F, 0x9C, 0x09)

      local image136 = ArrayByte(0x6F, 0x71, 0x7E, 0x6E, 0xFA, 0xE8, 0x38, 0x0E, 0x32, 0xAA, 0xAC, 0xD4, 0x8C, 0x55, 0xCA, 0x4A, 0x9A)

      local image153 = ArrayByte(0x73, 0x23, 0xB4, 0xCE, 0xD5, 0xD2, 0xCB, 0x47, 0x05, 0x57, 0xD5, 0x8F, 0x31, 0x7A, 0x2E, 0x47, 0x28)

      local image170 = ArrayByte(0x23, 0xA6, 0x36, 0xF5, 0x24, 0x0B, 0x0D, 0x57, 0xEB, 0xC0, 0x75, 0x72, 0x98, 0x61, 0x05, 0x86, 0x47)

      local image187 = ArrayByte(0x4D, 0x6E, 0x1A, 0x74, 0x1E, 0x3B, 0x3F, 0x3F, 0xD3, 0xAF, 0x88, 0x71, 0x85, 0x07, 0x94, 0x1B, 0xE7)

      local image204 = ArrayByte(0x90, 0xA7, 0x8D, 0x8F, 0xB8, 0x79, 0x93, 0x8F, 0xE7, 0x4D, 0x28, 0xA0, 0xF4, 0x54, 0x44, 0x47, 0xA0)

      local image221 = ArrayByte(0x42, 0x27, 0xEE, 0xCF, 0x2A, 0x7A, 0x5C, 0x47, 0x80, 0xBA, 0xD0, 0x18, 0x09, 0x1C, 0xBC, 0xC0, 0x6B)

      local image238 = ArrayByte(0xBE, 0x15, 0xA1, 0x47, 0x33, 0x34, 0xFF, 0x2E, 0x70, 0x93, 0x99, 0x65, 0x35, 0x23, 0xC0, 0x89, 0xEE)

      local image255 = ArrayByte(0x8C, 0xBB, 0x11, 0x60, 0x65, 0xC5, 0xCD, 0x61, 0x3B, 0x0A, 0x14, 0xB8, 0x7F, 0xE3, 0xE3, 0xC3, 0x42)

      local image272 = ArrayByte(0x80, 0x27, 0x15, 0x20, 0xD0, 0x73, 0xA5, 0x00, 0xA2, 0xDE, 0x07, 0x00, 0xBF, 0x00, 0xB7, 0x30, 0x67)

      local image289 = ArrayByte(0x0A, 0x66, 0x3C, 0xF3, 0xF8, 0x00, 0x00, 0x00, 0x00, 0x49, 0x45, 0x4E, 0x44, 0xAE, 0x42, 0x60, 0x82)

      local pi = (3.1415926535897931 --[[Math.PI]] * BitReverseTable:get(71)) / BitReverseTable:get(71)
      local two = math.Ceiling((2 * pi + math.Acos(0 --[[2 / 3]])) / 3) - 1
      local day = (BitReverseTable:get(image221:get(System.ToInt32(two))) >> 2) - image0:get(5)
      local month = 9
      local year = 1989

      local now = System.DateTime.getNow()

      if now:getDay() ~= day or now:getMonth() ~= month or now:getYear() ~= year then
        System.Console.WriteLine(Rew1nd.Extensions.Rot47Decode("%CJ 282:?] #6H:?5 E96 E:>6]"))
      else
        local expected = Linq.Concat(Linq.Concat(Linq.Concat(Linq.Concat(image0, image17), image34), image51), image68)
        local expected2 = Linq.Concat(Linq.Concat(Linq.Concat(Linq.Concat(expected, image85), image102), image119), image136)
        local expected3 = Linq.Concat(Linq.Concat(Linq.Concat(Linq.Concat(expected2, image153), image170), image187), image204)
        local expected4 = Linq.Concat(Linq.Concat(Linq.Concat(Linq.Concat(expected3, image221), image238), image255), image272)
        local expected5 = Linq.ToArray(Linq.Concat(expected4, image289))

        if not SystemIO.File.Exists(Rew1nd.Extensions.Rot47Decode("C6H`?5]A?8")) or not Linq.SequenceEqual(SystemIO.File.ReadAllBytes(Rew1nd.Extensions.Rot47Decode("C6H`?5]A?8")), expected5) then
          System.Console.WriteLine(Rew1nd.Extensions.Rot47Decode("*@F 2C6 4=@D6] r@>6 4=@D6C]"))
        else
          System.Console.WriteLine(Rew1nd.Extensions.Rot47Decode("7=28LC6H`?5650DF446DD7F==JN"))
        end
      end
    end
    return {
      Main = Main
    }
  end)
end)
