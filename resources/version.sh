VERSION=$(git describe --tags `git rev-list --tags --max-count=1`)
MAJOR="$(cut -d '.' -f1 <<< $VERSION)"
MINOR="$(cut -d '.' -f2 <<< $VERSION)"
PATCH="$(cut -d '.' -f3 <<< $VERSION)"

LAST_TAG_SHA=$(git rev-list -n 1 $VERSION)
CURRENT_SHA=$(git rev-parse HEAD)

if [ "$LAST_TAG_SHA" != "$CURRENT_SHA" ]; then
	PATCH=$((PATCH+1))
fi

NEW_VERSION=$MAJOR.$MINOR.$PATCH

echo $NEW_VERSION
