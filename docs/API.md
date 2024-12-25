# API Architecture and Documentation

## API Endpoints

### _User_ API

Root endpoint: `/api/v1/user`

Method: ___POST___

Description: Using the HTTP `POST` method, the system will trigger the creation of a new User with the given information provided in the payload sent.

HTTP Return codes:

- `400(Bad request)`: `username` parameter has not been provided or the username already exists. Details in the error message.
- `429(Unauthorized request)`: Rate limit the creation of a user by IP?
- `200(OK)`: User has been updated succesfully.

Method: ___PUT___

Description: Using the HTTP `PUT` method, the system will trigger an update of the user. The `username` parameter must be specified in the payload and must be an existing user.

HTTP Return codes:

- `400(Bad request)`: `username` parameter has not been provided.
- `401(Unauthorized request)`: Missing authorization to update the requested user. (Users can update their own user, not others.).
- `404(Not found)`: The specified username does not exists.
- `200(OK)`: User has been updated succesfully.

Method: ___GET___

Description: Using the HTTP `GET` method, the system will fetch the user information and returns it.

HTTP Return codes

- `400(Bad request)`: `username` parameter has not been provided.
- `401(Unauthorized request)`: Missing authorization to fetch the requested user. (Users can fetch their own user, not others.).
- `404(Not found)`: The specified username does not exists.
- `200(OK)`: User has been fetched succesfully.

JSON Payload Structure:
```json
{
    "username": "j.smith",
    "firstname": "John",
    "lastname": "Smith",
    "email": "j.smith@mail.com"
}
```