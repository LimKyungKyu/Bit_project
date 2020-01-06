// Auto-generated. Do not edit!

// (in-package project_ros_cpp.msg)


"use strict";

const _serializer = _ros_msg_utils.Serialize;
const _arraySerializer = _serializer.Array;
const _deserializer = _ros_msg_utils.Deserialize;
const _arrayDeserializer = _deserializer.Array;
const _finder = _ros_msg_utils.Find;
const _getByteLength = _ros_msg_utils.getByteLength;

//-----------------------------------------------------------

class clean_point {
  constructor(initObj={}) {
    if (initObj === null) {
      // initObj === null is a special case for deserialization where we don't initialize fields
      this.clean_data = null;
      this.max_gird_point = null;
    }
    else {
      if (initObj.hasOwnProperty('clean_data')) {
        this.clean_data = initObj.clean_data
      }
      else {
        this.clean_data = [];
      }
      if (initObj.hasOwnProperty('max_gird_point')) {
        this.max_gird_point = initObj.max_gird_point
      }
      else {
        this.max_gird_point = 0;
      }
    }
  }

  static serialize(obj, buffer, bufferOffset) {
    // Serializes a message object of type clean_point
    // Serialize message field [clean_data]
    bufferOffset = _arraySerializer.int32(obj.clean_data, buffer, bufferOffset, null);
    // Serialize message field [max_gird_point]
    bufferOffset = _serializer.int32(obj.max_gird_point, buffer, bufferOffset);
    return bufferOffset;
  }

  static deserialize(buffer, bufferOffset=[0]) {
    //deserializes a message object of type clean_point
    let len;
    let data = new clean_point(null);
    // Deserialize message field [clean_data]
    data.clean_data = _arrayDeserializer.int32(buffer, bufferOffset, null)
    // Deserialize message field [max_gird_point]
    data.max_gird_point = _deserializer.int32(buffer, bufferOffset);
    return data;
  }

  static getMessageSize(object) {
    let length = 0;
    length += 4 * object.clean_data.length;
    return length + 8;
  }

  static datatype() {
    // Returns string type for a message object
    return 'project_ros_cpp/clean_point';
  }

  static md5sum() {
    //Returns md5sum for a message object
    return 'fc3d368272e33463cb6bcfa0567b445f';
  }

  static messageDefinition() {
    // Returns full string definition for message
    return `
    int32[] clean_data
    int32 max_gird_point
    
    `;
  }

  static Resolve(msg) {
    // deep-construct a valid message object instance of whatever was passed in
    if (typeof msg !== 'object' || msg === null) {
      msg = {};
    }
    const resolved = new clean_point(null);
    if (msg.clean_data !== undefined) {
      resolved.clean_data = msg.clean_data;
    }
    else {
      resolved.clean_data = []
    }

    if (msg.max_gird_point !== undefined) {
      resolved.max_gird_point = msg.max_gird_point;
    }
    else {
      resolved.max_gird_point = 0
    }

    return resolved;
    }
};

module.exports = clean_point;
