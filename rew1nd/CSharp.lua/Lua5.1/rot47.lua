-- Generated by CSharp.lua Compiler
local System = System
local Linq = System.Linq.Enumerable
local SystemText = System.Text
local ListByte = System.List(System.Byte)
System.namespace("Rew1nd", function (namespace)
  namespace.class("Rot47", function (namespace)
    local ByteSequence, JoinByteArrays, rot47_it
    ByteSequence = function (min, max)
      return System.yieldIEnumerable(function (min, max)
        while min <= max do
          local default = min
          min = default + 1
          System.yield(default)
        end
      end, System.Byte, min, max)
    end
    JoinByteArrays = function (b1, b2)
      local l1 = Linq.ToList(b1)
      local l2 = Linq.ToList(b2)
      local l3 = ListByte()
      l3:AddRange(l1)
      l3:AddRange(l2)
      return l3:ToArray()
    end
    rot47_it = function (data)
      local alphabet = Linq.ToArray(ByteSequence(33, 126))

      local bytes = SystemText.Encoding.getASCII():GetBytes(data)
      local output = ListByte()
      for _, b in System.each(bytes) do
        local n = b
        if n < 33 or n > 126 then
          output:Add(n)
        else
          local v = (n - 33) + 47
          if v > 94 then
            v = v - 94
          end

          if v == 94 then
            v = 0
          end

          output:Add(alphabet:get(System.Convert.ToByte(v)))
        end
      end
      return SystemText.Encoding.getASCII():GetString(output:ToArray())
    end
    return {
      ByteSequence = ByteSequence,
      JoinByteArrays = JoinByteArrays,
      rot47_it = rot47_it,
      __metadata__ = function (out)
        return {
          methods = {
            { "ByteSequence", 0x28E, ByteSequence, System.Byte, System.Byte, System.IEnumerable_1(System.Byte) },
            { "JoinByteArrays", 0x28E, JoinByteArrays, System.Array(System.Byte), System.Array(System.Byte), System.Array(System.Byte) },
            { "rot47_it", 0x18E, rot47_it, System.String, System.String }
          },
          class = { 0x6 }
        }
      end
    }
  end)
end)